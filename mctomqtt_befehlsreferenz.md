# mctomqtt Service – Befehlsreferenz

**Node:** RpPiW-002 | **Service:** mctomqtt (MeshCore to MQTT Relay)  
**Pfad:** `/opt/mctomqtt/` | **Config:** `appsettings.json`  
**Erstellt:** 2026-07-19 | **Firmware:** 1.16.0 (Repeater mit Packet Logging)

---

## Service-Steuerung

| Aktion | Befehl |
|--------|--------|
| Status anzeigen | `sudo systemctl status mctomqtt` |
| Service starten | `sudo systemctl start mctomqtt` |
| Service stoppen | `sudo systemctl stop mctomqtt` |
| Service neustarten | `sudo systemctl restart mctomqtt` |
| Autostart aktivieren | `sudo systemctl enable mctomqtt` |
| Autostart deaktivieren | `sudo systemctl disable mctomqtt` |

---

## Logs & Monitoring

| Aktion | Befehl |
|--------|--------|
| Live-Log verfolgen | `sudo journalctl -u mctomqtt -f` |
| Letzte 50 Zeilen | `sudo journalctl -u mctomqtt -n 50` |
| Letzter Tail (ohne Pager) | `sudo journalctl -u mctomqtt -n 20 --no-pager` |
| Logs seit heute | `sudo journalctl -u mctomqtt --since today` |
| Logs seit bestimmter Zeit | `sudo journalctl -u mctomqtt --since "2026-07-19 14:00"` |
| Nur Fehler anzeigen | `sudo journalctl -u mctomqtt -p err` |

---

## Diagnose & Hardware

| Aktion | Befehl |
|--------|--------|
| USB-Geräte anzeigen | `lsusb` |
| Serielle Ports auflisten | `ls -la /dev/serial/by-id/` |
| Prüfen ob Prozess läuft | `ps aux | grep mctomqtt` |
| CPU/RAM des Service | `systemctl status mctomqtt` |
| Service-Datei anzeigen | `cat /etc/systemd/system/mctomqtt.service` |

---

## Konfiguration & Updates

| Aktion | Befehl |
|--------|--------|
| Config anzeigen | `cat /opt/mctomqtt/appsettings.json` |
| Config editieren | `sudo nano /opt/mctomqtt/appsettings.json` |
| Config sichern | `cp /opt/mctomqtt/appsettings.json ~/mctomqtt_config_backup.json` |
| Service nach Config-Änderung neu laden | `sudo systemctl daemon-reload && sudo systemctl restart mctomqtt` |
| Neuinstallation/Update | `curl -fsSL https://raw.githubusercontent.com/Cisien/meshcoretomqtt/main/install.sh | bash` |

---

## Notfall / Reset

| Aktion | Befehl |
|--------|--------|
| Service stoppen + USB trennen | `sudo systemctl stop mctomqtt` dann USB physisch trennen/stecken |
| Nach USB-Reset neu starten | `sleep 5 && sudo systemctl start mctomqtt` |
| Alle mctomqtt-Prozesse killen | `sudo pkill -f mctomqtt` |
| Kompletten Log löschen (Vorsicht!) | `sudo journalctl --vacuum-time=1d` |

---

## Top-3 Alltags-Befehle

```bash
# 1. Schneller Blick: "Läuft's?"
sudo systemctl status mctomqtt

# 2. Live mitschauen
sudo journalctl -u mctomqtt -f

# 3. Neustart nach Problem
sudo systemctl restart mctomqtt
```

---

## Wichtige Log-Zeilen interpretieren

| Log-Meldung | Bedeutung |
|-------------|-----------|
| `Serial reconnected successfully` | USB-Verbindung zum RAK-Modul hergestellt |
| `RX/TX: 5/2 (5m: 1.4/min)` | 5 Pakete empfangen, 2 gesendet, Rate OK |
| `RX bytes: 424B` | Gesamte empfangene Datenmenge |
| `MQTT: 2/2` | Beide MQTT-Broker verbunden |
| `Serial device unavailable` | USB-Verbindung unterbrochen – prüfe Kabel/Port |
| `Failed to connect to any serial port` | RAK-Modul nicht erkannt – USB-Reset nötig |
| `Air (5m): Tx 3.0s, Rx 23.0s` | Funk aktiv – sendet/empfängt |
| `Noise: -104dB` | Rauschpegel gut (< -95 dB ist OK) |

---

## Hinweise

- **Firmware 1.16.0** mit Packet Logging ist Voraussetzung dafür, dass der Repeater Pakete über Serial ausgibt
- Nach einem Firmware-Flash: `mctomqtt` neu installieren via install.sh
- Config-Backup vor jedem Update machen!
