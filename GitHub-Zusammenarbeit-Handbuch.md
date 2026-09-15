# GitHub-Zusammenarbeit – Komplett-Handbuch

Autor: Paul Simmen mit Vibe (GLM-5-2), 15.09.2026

---

## Hinweis

Dies ist eine Zusammenfassung. Das **vollständige Handbuch (29 KB)** findest du als **Canvas** in deiner Vibe-Umgebung unter: "GitHub-Zusammenarbeit – Komplett-Handbuch für Paul Simmen"

---

## Inhaltsverzeichnis

1. Grundlagen: Git & GitHub
2. Wie Vibe mit GitHub interagiert
3. Anweisungen an Vibe: Syntax und Beispiele
4. Typische Workflows
5. Sicherheit und Best Practices
6. Fehlerbehebung
7. Checklisten
8. Nützliche Ressourcen

---

## 1. Grundlagen: Git und GitHub

Git ist ein Versionskontrollsystem (VCS), das Aenderungen an Dateien nachverfolgt.
GitHub ist eine Cloud-Plattform fuer Git-Repositories.

Wichtige GitHub-Begriffe:
- Repository: Projektordner (z.B. Paul-3400/WwV)
- Branch: Parallele Version (z.B. main, feature/x)
- Commit: Momentaufnahme deiner Aenderungen
- Pull Request: Vorschlag zum Zusammenfuehren von Branches
- Issue: Aufgabe oder Bug-Report

---

## 2. Wie Vibe mit GitHub interagiert

Was Vibe kann:
- Repository: Erstellen, Loeschen, Forken, Einstellungen aendern
- Dateien: Erstellen, Bearbeiten, Loeschen, Verschieben
- Branches: Erstellen, Loeschen, Auflisten
- Commits: Erstellen, Anzeigen, Durchsuchen
- Pull Requests: Erstellen, Mergen, Kommentieren, Reviewen
- Issues: Erstellen, Bearbeiten, Kommentieren, Schliessen
- Releases: Erstellen, Auflisten

Was Vibe NICHT kann:
- Keine lokalen Git-Operationen (z.B. git commit im Terminal)
- Keine Code-Ausfuehrung (z.B. python script.py)
- Keine Kontenverwaltung
- Kein Undo fuer Loeschungen

---

## 3. Anweisungen an Vibe: Syntax und Beispiele

Grundregeln:
1. Sei spezifisch: Gib alle Parameter an (Repo, Branch, Dateipfad, etc.)
2. Verwende klare Befehle: Imperativ (Erstelle, Bearbeite, Loesche)
3. Strukturiere komplexe Anweisungen: Nummerierte Schritte
4. Vermeide Mehrdeutigkeiten: die Datei src/main.py statt die Datei

Beispiel fuer eine gute Anweisung:
Erstelle im Repository WwV im Branch main eine Datei docs/handbuch.md mit folgendem Inhalt: [Inhalt]. Commite mit Nachricht Handbuch hinzugefuegt.

Beispiel fuer eine schlechte Anweisung:
Erstelle eine Datei.

---

## 4. Typische Workflows

Neues Python-Projekt starten:
1. Repository erstellen
2. Dateien erstellen (README.md, src/__init__.py, .gitignore)
3. Initialen Commit mit Nachricht Projekt initialisiert
4. Branch main schuetzen (optional)

Bugfix in bestehendem Projekt:
1. Branch fix/negativer-radius von main erstellen
2. Datei src/geometrie.py bearbeiten
3. Test in tests/test_geometrie.py erstellen
4. Commite mit Nachricht Bugfix: Validierung fuer negativen Radius
5. Pull Request von fix/negativer-radius nach main erstellen

Feature hinzufuegen:
1. Branch feature/umfang-berechnung von main erstellen
2. Funktion in src/geometrie.py hinzufuegen
3. README.md aktualisieren
4. Commite mit Nachricht Feature: Umfang-Berechnung hinzugefuegt
5. Pull Request erstellen

---

## 5. Sicherheit und Best Practices

Geheimnisse schuetzen:
- NIEMALS API-Keys, Passwoerter oder andere Geheimnisse in Commits speichern!
- Nutze .env-Dateien fuer lokale Geheimnisse (aber fuege sie NICHT dem Repository hinzu!)
- Nutze GitHub Secrets fuer CI/CD-Pipelines (Settings > Secrets > Actions)

Branching-Strategie:
- main/master: Immer stabiler Code
- dev: Entwicklungszweig
- feature/x: Feature-Branches
- fix/x: Bugfix-Branches

Commit-Nachrichten:
Format: Typ(Bereich): Beschreibung
Beispiele:
- feat(geometrie): berechne_umfang hinzugefuegt
- fix(berechnung): Validierung fuer negativen Radius
- docs(readme): Autor aktualisiert

---

## 6. Fehlerbehebung

Fehler und Loesungen:
- Repository not found: Repo-Namen pruefen (z.B. Paul-3400/WwV)
- Branch not found: Branch erstellen oder zu bestehendem wechseln
- File not found: Dateipfad pruefen (relativ zum Repository-Root!)
- 403 Forbidden: Zugriff auf Repository pruefen
- 404 Not Found: Existenz der Ressource pruefen
- Conflict: Konflikt manuell oder mit git mergetool loesen
- Rate limit exceeded: Warten oder Anzahl der Anfragen reduzieren

---

## 7. Checklisten

Neues Projekt starten:
- [ ] Repository erstellen (Name, Beschreibung, privat/oentlich)
- [ ] .gitignore fuer Python erstellen
- [ ] README.md mit Projektbeschreibung erstellen
- [ ] src/ Verzeichnis mit __init__.py erstellen
- [ ] Erste Python-Datei(n) erstellen
- [ ] Initialen Commit erstellen

Feature hinzufuegen:
- [ ] Feature-Branch von main erstellen
- [ ] Code implementieren
- [ ] Tests schreiben
- [ ] Dokumentation aktualisieren
- [ ] Aenderungen commiten
- [ ] Pull Request erstellen

Bugfix:
- [ ] Bug reproduzieren
- [ ] Bugfix-Branch von main erstellen
- [ ] Fix implementieren
- [ ] Test schreiben
- [ ] Aenderungen commiten
- [ ] Pull Request erstellen

---

## 8. Nuetzliche Ressourcen

GitHub-Dokumentation:
- GitHub Docs (Deutsch): https://docs.github.com/de
- GitHub REST API: https://docs.github.com/en/rest
- GitHub CLI: https://cli.github.com/
- GitHub Desktop: https://desktop.github.com/

Git-Tutorials:
- Git – Die einfache Anleitung (Deutsch): https://rogerdudler.github.io/git-guide/index.de.html
- GitHub Guides (Englisch): https://guides.github.com/
- Learn Git Branching (Interaktiv): https://learngitbranching.js.org/

Python und GitHub:
- Python Packaging User Guide: https://packaging.python.org/
- PyPI: https://pypi.org/
- GitHub Actions fuer Python: https://docs.github.com/en/actions/automating-builds-and-tests/building-and-testing-python

Tools:
- Thonny IDE: https://thonny.org/
- VS Code: https://code.visualstudio.com/
- GitKraken: https://www.gitkraken.com/
- Sourcetree: https://www.sourcetreeapp.com/

Community:
- GitHub Community Forum: https://github.community/
- Stack Overflow: https://stackoverflow.com/
- GitHub Status: https://www.githubstatus.com/

---

## Zusammenfassung: Die 10 wichtigsten Punkte

1. Vibe kann fast alles auf GitHub – aber nur in deinen Repos oder geforkten Repos
2. Sei praezise in deinen Anweisungen (Repo, Branch, Dateipfad, Inhalt)
3. Nutze Branches fuer neue Features/Bugfixes (nie direkt in main arbeiten!)
4. Commite oft mit guten Nachrichten
5. Nutze Pull Requests fuer Code-Reviews und Zusammenfuehrung
6. Schuetze Geheimnisse (.env, GitHub Secrets)
7. Halte Repos aufgeraeumt (.gitignore, Branches bereinigen)
8. Nutze Issues fuer Aufgaben und Bugs
9. Nutze Releases/Tags fuer Versionierung
10. Falls Fehler auftreten: Vibe hilft dir beim Debugging!

---

WICHTIG: Das vollstaendige Handbuch (29 KB) mit allen Details, Beispielen, Workflows, Checklisten und Ressourcen findest du als Canvas in deiner Vibe-Umgebung!

Autor: Paul Simmen mit Vibe (GLM-5-2), 15.09.2026