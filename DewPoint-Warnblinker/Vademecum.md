# 📖 Vademecum – DewPoint-Warnblinker (ESP32)

Erstellt von Paul Simmen mit Vibe, 14.09.2026.

ESP32-Warnblinker, der vor dem **Überschreiten des kritischen Taupunktes**
(Kondensatbildung / Schwitzwasser) warnt.

---

## 🎯 Zweck

Sobald die Differenz zwischen aktueller Umgebungstemperatur und dem
Taupunkt klein wird, steigt die Gefahr, dass sich Kondensat (Wasser) an
Oberflächen bildet – z. B. an Elektronik, an Wänden, im Schaltschrank
oder in Lagerbereichen. Der Blinker macht diese Gefahr sichtbar, **bevor**
es zur Kondensatbildung kommt.

---

## 🔧 Hardware

| Bauteil | Wert / Typ | Anschluss |
|---|---|---|
| Mikrocontroller | ESP32 (DevKit V1) | – |
| Stromversorgung | 5 V USB | USB-Buchse / 5V-Pin |
| LED | Standard-LED (rot empfohlen) | Anode → Vorwiderstand → GPIO 2 |
| Vorwiderstand | 220 … 470 Ω | zwischen LED-Anode und GPIO 2 |
| Umwelt-Sonde | AHT20 (Temp. + rel. Feuchte, I²C 0x38) | SDA → GPIO 21, SCL → GPIO 22 |
| I²C-Pullups | 4,7 kΩ (oft onboard) | SDA/SCL nach 3,3 V |

> Der ESP32 läuft mit 3,3 V Logik. Der AHT20 verträgt 3,3 V direkt.
> Die LED wird ebenfalls vom 3,3 V-Pegel geschaltet – Vorwiderstand
> dimensionieren für ~5..10 mA (rot: 220 Ω ist üblich).

### Verdrahtung

```
   ESP32                    AHT20
   GPIO 21 (SDA) ────────── SDA
   GPIO 22 (SCL) ────────── SCL
   3V3           ────────── VDD
   GND           ────────── GND

   ESP32                    LED
   GPIO 2 ──[ 220 Ω ]──┬── LED-Anode
                       └── LED-Kathode ── GND
```

---

## ⚙️ Funktionsweise

1. Der AHT20 liefert alle 2 s Temperatur `T` und relative Feuchte `rH`.
2. Der Taupunkt `Tp` wird mit der **Magnus-Formel** berechnet:
   ```
   α = (17,625 · T) / (243,04 + T)
   γ = ln(rH/100) + α
   Tp = (243,04 · γ) / (17,625 − γ)
   ```
3. Bewertet wird die **Differenz** `Diff = T − Tp` (Spreizung).

### Warnstufen (Schwellwerte konfigurierbar im Sketch)

| Stufe | Bedingung | LED-Verhalten |
|---|---|---|
| OK | Diff > 3,0 °C | langsames Pulsieren (2 s) |
| WARNUNG | 1,5 °C < Diff ≤ 3,0 °C | mittleres Blinken (500 ms) |
| KRITISCH | Diff ≤ 1,5 °C | schnelles Blinken (150 ms) → akute Kondensatgefahr |

> Schwellwerte (`SCHWELL_WARN`, `SCHWELL_KRITISCH`) im Sketch anpassen.

---

## 🧰 Bibliotheken (Arduino IDE / PlatformIO)

- `Wire` (Arduino-Core)
- `Adafruit AHTX0` (Library-Manager: **"Adafruit AHTX0"**)

Installieren in der Arduino IDE:
`Werkzeuge → Bibliotheken verwalten → Suchen: "Adafruit AHTX0" → Installieren`.

---

## 🚀 Inbetriebnahme

| Schritt | Aktion |
|---|---|
| 1 | USB-Kabel an ESP32 (5 V Versorgung) |
| 2 | Board "ESP32 Dev Module" wählen, richtigen COM-Port einstellen |
| 3 | Sketch `DewPoint_Warnblinker.ino` hochladen |
| 4 | Seriellen Monitor öffnen: **115200 Baud** |
| 5 | Ausgabe prüfen: `T=..  rH=..  Tp=..  Diff=.. -> OK/WARNUNG/KRITISCH` |
| 6 | LED-Verhalten je nach Luftfeuchte beobachten |

Serielle Ausgabe (Beispiel):
```
AHT20-Sensor gefunden (0x38).
DewPoint-Warnblinker gestartet.
T=21.4 C  rH=68.3 %  Tp=15.1 C  Diff=6.3 C  -> OK
T=21.1 C  rH=82.1 %  Tp=18.0 C  Diff=3.1 C  -> WARNUNG
T=20.9 C  rH=92.7 %  Tp=19.5 C  Diff=1.4 C  -> KRITISCH (Kondensatgefahr!)
```

---

## 🧪 Sensor prüfen / Fehlerbehebung

| Befehl / Prüfung | Beschreibung |
|---|---|
| `i2cdetect -y …` (falls ESP32-Toolchain) | I²C-Scan (AHT20 auf 0x38) |
| Seriell: `FEHLER: AHT20 nicht gefunden!` | Verkabelung/Adress-Pullups prüfen |
| LED bleibt dunkel | `sensor_ok == false` → Sensor nicht erkannt |
| LED blinkt nicht | Schwellwerte evtl. zu eng → Diff im Monitor prüfen |
| Feuchtewerte 0 % / 100 % | Sensor anatmen / kalibrieren lassen (Aufwärmzeit) |

---

## 📁 Dateien

| Datei | Inhalt |
|---|---|
| `DewPoint_Warnblinker.ino` | Arduino-Sketch (ESP32, AHT20, LED-Blinker) |
| `Vademecum.md` | Diese Befehls-/Aufbaureferenz |

---

## 🔧 Anpassungen (Schnellübersicht im Sketch)

| Konstante | Default | Bedeutung |
|---|---|---|
| `LED_PIN` | 2 | GPIO der LED |
| `I2C_SDA` / `I2C_SCL` | 21 / 22 | I²C-Pins |
| `SCHWELL_WARN` | 3.0 °C | Vorwarn-Schwelle |
| `SCHWELL_KRITISCH` | 1.5 °C | Akut-Schwelle (Kondensat) |
| `MESS_INTERVALL_MS` | 2000 | Mess-Intervall |

---

## 📝 Notiz

Dieser Warnblinker ist eine **Vorwarnung** – er ersetzt keine echte
Kondensat-Vermeidung (Belüftung, Heizung, Isolierung). Schwellwerte an
den jeweiligen Einsatort (Keller, Schaltschrank, Gewächshaus …) anpassen.
