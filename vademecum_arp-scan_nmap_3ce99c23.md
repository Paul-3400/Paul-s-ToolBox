# 📋 Vademecum: `arp-scan` & `nmap` – Befehlsreferenz

> **Autor:** Paul's MeshCore & ElektroTech Buddy  
> **Datum:** 20. Juli 2026  
> **Plattform:** macOS (MacBook Air) / Linux (Raspberry Pi)  
> **Voraussetzung:** Installation via `brew install arp-scan nmap`

---

Du siehst zwei Netzwerk-Adressen:
Adresse	Bedeutung
127.0.0.1	Das ist dein Mac, der mit sich selbst redet (Loopback – kannst du ignorieren)

10.0.1.184	Das ist die echte IP deines Macs im WLAN! ✅
🔑 Die wichtige Erkenntnis:
Dein Heimnetz verwendet nicht 192.168.1.x (wie bei Swisscom üblich), sondern:

10.0.1.x mit Broadcast 10.0.1.255

Das heisst: Dein Router vergibt Adressen im Bereich 10.0.1.x.

✅ Dein korrekter Scan-Befehl lautet also:
bash


sudo arp-scan -I en0 10.0.1.0/24 | grep -i raspberry
Oder ohne Filter (alle Geräte sehen):

bash


sudo arp-scan -I en0 10.0.1.0/24
📦 Zusammenfassung in einem Satz:
Dein Mac hängt im Netz 10.0.1.x – du musst diesen Bereich scannen, nicht 192.168.1.x

## 1. arp-scan – Der schnelle Netzwerk-Überblick

### Grundprinzip

`arp-scan` sendet ARP-Requests an alle Adressen im lokalen Netz und listet antwortende Geräte mit IP, MAC-Adresse und Hersteller auf. Schnell, schlank, zuverlässig.

### Wichtige Befehle

| Befehl | Beschreibung |
|--------|-------------|
| `sudo arp-scan --localnet` | Scannt das gesamte lokale Netz (automatische Interface-Erkennung) |
| `sudo arp-scan -I en0 --localnet` | Scan explizit über WLAN-Interface `en0` |
| `sudo arp-scan -I eth0 --localnet` | Scan über Ethernet (z. B. am Raspberry Pi) |
| `sudo arp-scan 192.168.1.0/24` | Scannt nur das angegebene Subnetz |
| `sudo arp-scan 192.168.1.40-60` | Scannt nur einen IP-Bereich (.40 bis .60) |
| `sudo arp-scan --localnet --retry=3` | 3 Versuche pro Host (findet "schlafende" Geräte) |
| `sudo arp-scan --localnet --ignoredups` | Doppelte Antworten unterdrücken |
| `sudo arp-scan --localnet -x` | Nur IP und MAC ausgeben (ohne Header/Footer) |

### Ausgabe interpretieren

```
192.168.1.1     00:1a:2b:3c:4d:5e    Swisscom (Schweiz) AG
192.168.1.42    dc:a6:32:12:34:56    Raspberry Pi Trading Ltd
192.168.1.55    b8:27:eb:aa:bb:cc    Raspberry Pi Foundation
192.168.1.100   a4:83:e7:xx:xx:xx    Apple, Inc.
```

- **Spalte 1:** IP-Adresse
- **Spalte 2:** MAC-Adresse (Hardware-Adresse)
- **Spalte 3:** Hersteller (basierend auf den ersten 3 Byte der MAC)

### Tipps & Tricks

```bash
# Ergebnis in Datei speichern
sudo arp-scan --localnet > ~/Desktop/netzwerk_scan.txt

# Nur Raspberry Pis finden
sudo arp-scan --localnet | grep -i "raspberry"

# Nur unbekannte Geräte finden (nicht Swisscom, nicht Apple, nicht Raspberry)
sudo arp-scan --localnet | grep -iv "swisscom\|apple\|raspberry"

# Ergebnis sortiert nach IP
sudo arp-scan --localnet | sort -t. -k4 -n
```

---

## 2. nmap – Der mächtige Netzwerk-Scanner

### Grundprinzip

`nmap` (Network Mapper) ist das Schweizer Taschenmesser der Netzwerk-Analyse. Es kann Hosts entdecken, offene Ports finden, Dienste identifizieren und Betriebssysteme erkennen.

### 2.1 Host-Discovery (Wer ist online?)

| Befehl | Beschreibung |
|--------|-------------|
| `sudo nmap -sn 192.168.1.0/24` | Ping-Scan: nur prüfen wer online ist (keine Port-Scans) |
| `sudo nmap -sn 192.168.1.40-60` | Nur einen Bereich scannen |
| `sudo nmap -sn -PR 192.168.1.0/24` | ARP-Ping (zuverlässigster Scan im LAN) |
| `nmap -sL 192.168.1.0/24` | Nur DNS-Auflösung, kein Scan (listet Hostnamen) |

### 2.2 Port-Scanning (Was läuft auf dem Gerät?)

| Befehl | Beschreibung |
|--------|-------------|
| `nmap 192.168.1.42` | Standard-Scan der 1000 häufigsten Ports |
| `nmap -p 22,80,443 192.168.1.42` | Nur bestimmte Ports scannen |
| `nmap -p 1-65535 192.168.1.42` | ALLE Ports scannen (dauert länger) |
| `nmap -p- 192.168.1.42` | Kurzform für alle 65535 Ports |
| `nmap --top-ports 100 192.168.1.42` | Die 100 häufigsten Ports |
| `sudo nmap -sU -p 53,67,68,161 192.168.1.1` | UDP-Ports scannen (z. B. DNS, DHCP) |

### 2.3 Dienst- und Versions-Erkennung

| Befehl | Beschreibung |
|--------|-------------|
| `nmap -sV 192.168.1.42` | Dienste + Versionsnummern erkennen |
| `nmap -sV --version-intensity 5 192.168.1.42` | Intensivere Versionserkennung (0-9) |
| `sudo nmap -O 192.168.1.42` | Betriebssystem erkennen |
| `sudo nmap -A 192.168.1.42` | Aggressiv: OS + Dienste + Traceroute + Scripts |

### 2.4 Nützliche Kombinationen

```bash
# Kompletter Netzwerk-Überblick: Wer ist da + was läuft?
sudo nmap -sn 192.168.1.0/24 -oG - | grep "Up" | awk '{print $2}'

# Alle Webserver im Netz finden
nmap -p 80,443,8080,8443 --open 192.168.1.0/24

# SSH-fähige Geräte finden (z. B. deine Raspberry Pis)
nmap -p 22 --open 192.168.1.0/24

# MeshCore-relevante Ports prüfen (TCP 5000, 4403 etc.)
nmap -p 4403,5000,8080 --open 192.168.1.0/24

# Schneller Scan mit OS-Erkennung
sudo nmap -sn -O 192.168.1.0/24
```

### 2.5 Ausgabe speichern

| Befehl | Beschreibung |
|--------|-------------|
| `nmap ... -oN scan.txt` | Normal-Format (menschenlesbar) |
| `nmap ... -oG scan.gnmap` | Grep-Format (gut zum Filtern) |
| `nmap ... -oX scan.xml` | XML-Format (für Weiterverarbeitung) |
| `nmap ... -oA scan_ergebnis` | Alle 3 Formate gleichzeitig |

**Beispiel:**
```bash
sudo nmap -sV 192.168.1.0/24 -oN ~/Desktop/netzwerk_details.txt
```

### 2.6 Timing & Performance

| Option | Beschreibung |
|--------|-------------|
| `-T0` | Paranoid (sehr langsam, unauffällig) |
| `-T1` | Sneaky |
| `-T2` | Polite (schont das Netzwerk) |
| `-T3` | Normal (Standard) |
| `-T4` | Aggressive (schnell, für LAN empfohlen) |
| `-T5` | Insane (sehr schnell, kann Ergebnisse verfälschen) |

**Empfehlung für Heimnetz:**
```bash
sudo nmap -T4 -sn 192.168.1.0/24
```

---

## 3. Vergleich: Wann was verwenden?

| Aufgabe | Tool | Befehl |
|---------|------|--------|
| Schnell: Wer ist im Netz? | arp-scan | `sudo arp-scan --localnet` |
| Detailliert: Wer ist im Netz? | nmap | `sudo nmap -sn 192.168.1.0/24` |
| Welche Ports sind offen? | nmap | `nmap 192.168.1.42` |
| Welcher Dienst läuft auf Port X? | nmap | `nmap -sV -p X 192.168.1.42` |
| Welches Betriebssystem? | nmap | `sudo nmap -O 192.168.1.42` |
| Einen Raspberry Pi finden | arp-scan | `sudo arp-scan --localnet \| grep -i raspberry` |
| Alle SSH-Geräte finden | nmap | `nmap -p 22 --open 192.168.1.0/24` |
| Netzwerk dokumentieren | nmap | `sudo nmap -sV -oN bericht.txt 192.168.1.0/24` |

---

## 4. Eigenes Subnetz ermitteln (Voraussetzung!)

```bash
# macOS: WLAN-IP herausfinden
ipconfig getifaddr en0

# macOS: Alle Interfaces anzeigen
ifconfig | grep "inet "

# Linux (Raspberry Pi):
ip addr show wlan0
hostname -I
```

**Typisch Swisscom:** `192.168.1.x/24` → Scan-Bereich: `192.168.1.0/24`

---

## 5. MAC-Adressen nachschlagen

Wenn du einen unbekannten Hersteller siehst:

- **Online:** https://macvendors.com
- **Terminal:** Die ersten 3 Byte der MAC (z. B. `DC:A6:32`) identifizieren den Hersteller

### Bekannte Raspberry Pi MACs:

| Prefix | Hersteller |
|--------|-----------|
| `DC:A6:32` | Raspberry Pi Trading Ltd (Pi 4, 5) |
| `B8:27:EB` | Raspberry Pi Foundation (Pi 3 und älter) |
| `D8:3A:DD` | Raspberry Pi Trading Ltd (Pi 5, neuere) |
| `2C:CF:67` | Raspberry Pi (Pi Zero 2 W) |

---

## 6. Häufige Szenarien – Schnellreferenz

### "Ich habe einen Pi eingesteckt, finde ihn aber nicht"
```bash
sudo arp-scan --localnet | grep -i raspberry
# oder
sudo nmap -sn 192.168.1.0/24 | grep -B 2 -i "raspberry"
```

### "Welches Gerät hat IP .42 und was macht es?"
```bash
sudo nmap -A 192.168.1.42
```

### "Ich will alle Geräte mit offenen Web-Interfaces finden"
```bash
nmap -p 80,443,8080 --open 192.168.1.0/24
```

### "Läuft mein MQTT-Broker (Port 1883)?"
```bash
nmap -p 1883 192.168.1.42
```

### "Regelmässigen Scan speichern (Cronjob)"
```bash
# Crontab öffnen (auf dem Pi)
crontab -e

# Alle 30 Minuten scannen und speichern
*/30 * * * * sudo arp-scan --localnet > /home/paul/logs/netzwerk_$(date +\%Y\%m\%d_\%H\%M).txt
```

---

## 7. Wichtige Hinweise

- ⚠️ **sudo erforderlich:** Die meisten Scans brauchen Root-Rechte (wegen Raw Sockets)
- 🏠 **Nur im eigenen Netz scannen!** Scans in fremden Netzen sind illegal
- 🐢 **Geduld bei nmap:** Vollständige Scans mit `-A` oder `-p-` können mehrere Minuten dauern
- 🔄 **Wiederholte Scans:** Manche Geräte antworten nicht beim ersten Mal (Sleep-Mode, WLAN-Powersave)

---

*Erstellt für Paul – Viel Spass beim Netzwerk-Erkunden! 🔍🖥️*
