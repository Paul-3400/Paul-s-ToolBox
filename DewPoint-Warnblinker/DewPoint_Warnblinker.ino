/*
 * DewPoint-Warnblinker
 * ------------------------------------------------------------------
 * ESP32-Warnblinker, der vor dem Ueberschreiten des kritischen
 * Taupunktes (Kondensatbildung) warnt.
 *
 * Hardware:
 *   - ESP32 (DevKit, USB 5V-Stromversorgung)
 *   - LED + Vorwiderstand (z.B. 220..470 Ohm) an GPIO 2
 *   - Umwelt-Sonde Temperatur/Feuchte (AHT20, I2C 0x38)
 *     SDA -> GPIO 21, SCL -> GPIO 22
 *
 * Funktion:
 *   Taupunkt aus Temperatur + rel. Feuchte nach der Magnus-Formel.
 *   Je kleiner die Differenz (T_ambient - T_taupunkt), desto groesser
 *   die Kondensationsgefahr. Unterschreitet die Differenz den
 *   SCHWELLwert, blinkt die LED als Warnung; wird sie noch kleiner
 *   (KRITISCH), blinkt die LED schneller (akute Kondensatgefahr).
 *
 * Bibliothek:
 *   Adafruit AHTX0  (Adafruit_AHTX0)  -  "Adafruit AHTX0"
 *   Wire (Arduino-Core)
 *
 * Autor: Paul Simmen mit Vibe, 14.09.2026
 */

#include <Wire.h>
#include <Adafruit_AHTX0.h>

// ------------------------- Pin-Definitionen -------------------------
static const uint8_t LED_PIN       = 2;   // interne/onboard LED beim ESP32
static const uint8_t I2C_SDA       = 21;
static const uint8_t I2C_SCL       = 22;

// ------------------------- Schwellwerte (Grad Celsius) -------------
// Differenz zwischen Umgebungstemperatur und Taupunkt.
static const float SCHWELL_WARN   = 3.0;  // gelb/normal Blinken -> Vorwarnung
static const float SCHWELL_KRITISCH = 1.5;  // schnell Blinken -> akute Kondensatgefahr

// ------------------------- Mess-Intervall ---------------------------
static const uint32_t MESS_INTERVALL_MS = 2000;  // alle 2 s neu messen

// ------------------------- Sensor -----------------------------------
Adafruit_AHTX0 aht;
bool sensor_ok = false;

// ------------------------- Taupunkt (Magnus-Formel) -----------------
// a, b: Magnus-Koeffizienten (gueltig ~ -45..+60 Grad C)
static const float MAGNUS_A = 17.625f;
static const float MAGNUS_B = 243.04f;

float berechne_taupunkt(float t_celsius, float rel_feuchte) {
  if (rel_feuchte <= 0.0f) rel_feuchte = 0.0001f;
  if (rel_feuchte > 100.0f) rel_feuchte = 100.0f;
  float alpha = (MAGNUS_A * t_celsius) / (MAGNUS_B + t_celsius);
  float gamma = logf(rel_feuchte / 100.0f) + alpha;
  return (MAGNUS_B * gamma) / (MAGNUS_A - gamma);
}

// ------------------------- LED-Warnstatus ---------------------------
enum WarnStufe { OK, WARNUNG, KRITISCH };

WarnStufe bewerte(float t_ambient, float t_taupunkt) {
  float diff = t_ambient - t_taupunkt;  // je kleiner, desto gefaehrlicher
  if (diff <= SCHWELL_KRITISCH) return KRITISCH;
  if (diff <= SCHWELL_WARN)     return WARNUNG;
  return OK;
}

void setup() {
  Serial.begin(115200);
  delay(200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Wire.begin(I2C_SDA, I2C_SCL);

  if (aht.begin(&Wire)) {
    sensor_ok = true;
    Serial.println(F("AHT20-Sensor gefunden (0x38)."));
  } else {
    sensor_ok = false;
    Serial.println(F("FEHLER: AHT20 nicht gefunden! Verkabelung/Adresse pruefen."));
  }

  Serial.println(F("DewPoint-Warnblinker gestartet."));
}

uint32_t letzte_messung = 0;
float t_ambient = NAN;
float rel_feuchte = NAN;
float t_taupunkt = NAN;
WarnStufe stufe = OK;

// Blink-Timing (nicht blockierend)
uint32_t letzter_flip = 0;
bool led_an = false;

uint32_t blink_periode_ms(WarnStufe s) {
  switch (s) {
    case KRITISCH: return 150;   // schnelles Blinken
    case WARNUNG:  return 500;  // mittleres Blinken
    case OK:       return 2000; // langsames "alles gut"-Pulsieren
    default:       return 2000;
  }
}

void loop() {
  uint32_t jetzt = millis();

  // 1) periodisch messen
  if (jetzt - letzte_messung >= MESS_INTERVALL_MS) {
    letzte_messung = jetzt;

    if (sensor_ok) {
      sensors_event_t hum, temp;
      if (aht.getEvent(&hum, &temp)) {
        t_ambient   = temp.temperature;
        rel_feuchte = hum.relative_humidity;
        t_taupunkt  = berechne_taupunkt(t_ambient, rel_feuchte);
        stufe       = bewerte(t_ambient, t_taupunkt);

        Serial.print(F("T="));   Serial.print(t_ambient, 1);
        Serial.print(F(" C  rH=")); Serial.print(rel_feuchte, 1);
        Serial.print(F(" %  Tp=")); Serial.print(t_taupunkt, 1);
        Serial.print(F(" C  Diff=")); Serial.print(t_ambient - t_taupunkt, 1);
        Serial.print(F(" C  -> "));
        switch (stufe) {
          case KRITISCH: Serial.println(F("KRITISCH (Kondensatgefahr!)")); break;
          case WARNUNG:  Serial.println(F("WARNUNG")); break;
          case OK:       Serial.println(F("OK")); break;
        }
      } else {
        Serial.println(F("Sensor-Lesefehler."));
      }
    } else {
      // Kein Sensor -> Dauer-LED aus, kein Blinken
      digitalWrite(LED_PIN, LOW);
    }
  }

  // 2) nicht-blockierendes Blinken
  if (sensor_ok) {
    uint32_t periode = blink_periode_ms(stufe);
    if (jetzt - letzter_flip >= periode / 2) {
      letzter_flip = jetzt;
      led_an = !led_an;
      digitalWrite(LED_PIN, led_an ? HIGH : LOW);
    }
  }
}
