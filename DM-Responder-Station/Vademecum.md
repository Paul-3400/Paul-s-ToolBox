# 📖 Vademecum – Befehlsreferenz MeshCore Responder-Station

Erstellt von Paul (Brain Gym) mit Hilfe von Claude (Anthropic, 22.06.2026).

## 🔧 Service-Management

| Befehl | Beschreibung |
|---|---|
| sudo systemctl start dm-responder | Service starten |
| sudo systemctl stop dm-responder | Service stoppen |
| sudo systemctl restart dm-responder | Service neu starten |
| sudo systemctl status dm-responder | Status pruefen |
| sudo systemctl enable dm-responder | Autostart bei Boot aktivieren |
| sudo systemctl disable dm-responder | Autostart deaktivieren |
| sudo journalctl -u dm-responder -f | Live-Logs anzeigen |
| sudo journalctl -u dm-responder --no-pager -n 30 | Letzte 30 Zeilen |

## 📡 Hotspot-Service

| Befehl | Beschreibung |
|---|---|
| sudo systemctl start hotspot-toggle | Hotspot-Service starten |
| sudo systemctl stop hotspot-toggle | Hotspot-Service stoppen |
| sudo systemctl restart hotspot-toggle | Hotspot-Service neu starten |
| sudo systemctl status hotspot-toggle | Status pruefen |
| sudo journalctl -u hotspot-toggle -f | Live-Logs Hotspot |
| sudo systemctl unmask hostapd | hostapd freigeben (nach OS-Update!) |

## 📂 Dateien & Navigation

| Befehl | Beschreibung |
|---|---|
| cd /home/paul-rppi/meshcore-responder | Projekt-Verzeichnis |
| ls -la | Dateien auflisten mit Details |
| cat station.conf | Konfiguration anzeigen |
| cat auth.conf | Passwort-Hash anzeigen |
| nano -lmi dateiname.py | Datei im Editor oeffnen (Zeilen+Maus) |
| head -30 dateiname.py | Erste 30 Zeilen anzeigen |
| tail -20 dateiname.py | Letzte 20 Zeilen anzeigen |
| grep -n "suchbegriff" dateiname.py | Suchen mit Zeilennummer |
| grep -rn "suchbegriff" *.py | In allen Python-Dateien suchen |

## 🌐 Netzwerk

| Befehl | Beschreibung |
|---|---|
| hostname -I | Eigene IP-Adressen anzeigen |
| ip addr show wlan0 | WLAN-Interface Details |
| ping -c 3 10.0.1.1 | Netzwerkverbindung testen |
| curl http://10.0.50.1:5000/ | Dashboard via Hotspot testen |
| curl http://10.0.1.167:5000/ | Dashboard via LAN testen |
| ss -tlnp \| grep 5000 | Pruefen ob Port 5000 lauscht |

## 🔌 GPIO & Hardware

| Befehl | Beschreibung |
|---|---|
| ls /dev/gpiochip* | Verfuegbare GPIO-Chips anzeigen |
| ls /dev/ttyACM* | USB-Serial Geraete (MeshCore Radio) |
| i2cdetect -y 1 | I2C-Bus scannen (Sensoren finden) |
| vcgencmd measure_temp | CPU-Temperatur |
| cat /proc/cpuinfo | CPU-Info + Seriennummer |
| df -h | Festplattenbelegung |
| free -h | Speicherauslauf |
| uptime | Laufzeit + Last |

## 🐍 Python & Pakete

| Befehl | Beschreibung |
|---|---|
| python3 --version | Python-Version |
| pip list | Installierte Pakete |
| pip install flask bcrypt meshcore_py smbus2 | Abhaengigkeiten installieren |
| python3 -c "import bcrypt; print(bcrypt.__version__)" | Paket-Version pruefen |
| python3 dateiname.py | Script manuell ausfuehren |

## 🧪 Debugging & Troubleshooting

| Befehl | Beschreibung |
|---|---|
| sudo journalctl -u dm-responder --no-pager -n 50 | Letzte 50 Log-Zeilen |
| sudo journalctl -u dm-responder --since "10 min ago" | Logs der letzten 10 Min |
| ps aux \| grep python | Laufende Python-Prozesse |
| sudo kill -9 PID | Prozess hart beenden |
| sudo systemctl daemon-reload | Nach Service-File Aenderung |
| dmesg \| tail -20 | Kernel-Meldungen (USB, GPIO) |
| lsusb | USB-Geraete auflisten |
| cat /var/log/syslog \| tail -30 | System-Log |

## 📋 CSV-Daten

| Befehl | Beschreibung |
|---|---|
| cat data/DMLOG.CSV | DM-Log anzeigen |
| cat data/CHANNELS.CSV | Channel-Log anzeigen |
| cat data/CONTACTS.CSV | Kontakte anzeigen |
| cat data/ENVLOG.CSV | Umweltdaten anzeigen |
| wc -l data/*.CSV | Zeilen zaehlen (Anzahl Eintraege) |
| head -5 data/ENVLOG.CSV | Erste 5 Eintraege |
| tail -10 data/DMLOG.CSV | Letzte 10 DMs |

## 🔐 Authentifizierung

| Befehl | Beschreibung |
|---|---|
| cat auth.conf | Aktuellen Passwort-Hash anzeigen |
| rm auth.conf | Passwort zuruecksetzen (Default admin/admin) |
| python3 -c "import bcrypt; print(bcrypt.hashpw(b'neuespasswort', bcrypt.gensalt()).decode())" | Hash manuell erzeugen |

## 📡 MeshCore Radio

| Befehl | Beschreibung |
|---|---|
| ls /dev/ttyACM* | Radio-Device pruefen |
| python3 -c "from meshcore_py import MeshCore; print('OK')" | Library-Import testen |
| screen /dev/ttyACM0 115200 | Serielle Konsole (Ctrl+A, K zum Beenden) |

## 💾 Backup & Transfer

| Befehl | Beschreibung |
|---|---|
| cp datei datei.bak | Lokales Backup |
| tar -czf backup_$(date +%y%m%d).tar.gz data/ | CSV-Daten archivieren |
| scp datei paul-rppi@10.0.1.167:/pfad/ | Datei auf Pi kopieren (vom Mac) |
| scp paul-rppi@10.0.1.167:/pfad/datei ~/Desktop/ | Datei vom Pi auf Mac (vom Mac) |

## 🔄 System

| Befehl | Beschreibung |
|---|---|
| sudo reboot | Neustart |
| sudo shutdown -h now | Herunterfahren |
| sudo apt update && sudo apt upgrade | System aktualisieren |
| cat /etc/os-release | OS-Version anzeigen |
| uname -a | Kernel-Info |

## 🌡️ Sensoren testen

| Befehl | Beschreibung |
|---|---|
| i2cdetect -y 1 | I2C-Adressen scannen (0x38=AHT20, 0x77=BMP280) |
| python3 -c "import smbus2; bus=smbus2.SMBus(1); print('I2C OK')" | I2C-Bus testen |

## 📝 Editor (nano)

| Tastenkombination | Beschreibung |
|---|---|
| nano -lmi datei | Oeffnen mit Zeilennummern + Maus |
| Ctrl+O | Speichern |
| Ctrl+X | Beenden |
| Ctrl+W | Suchen |
| Ctrl+K | Zeile ausschneiden |
| Ctrl+U | Zeile einfuegen |
| Alt+G | Zu Zeile springen |

## 🔗 Wichtige Pfade

| Pfad | Inhalt |
|---|---|
| /home/paul-rppi/meshcore-responder/ | Projekt-Hauptverzeichnis |
| /home/paul-rppi/hotspot_button.py | Hotspot-Toggle Script |
| /etc/systemd/system/dm-responder.service | Service-Definition |
| /etc/systemd/system/hotspot-toggle.service | Hotspot-Service-Definition |
| /etc/hostapd/hostapd.conf | Hotspot-Konfiguration (SSID, PW) |
