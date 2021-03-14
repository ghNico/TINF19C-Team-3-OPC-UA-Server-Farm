# Inhaltsverzeichnis

[Meeting 14.10.2020](#meeting-1)

[Meeting 16.10.2020](#meeting-2)

[Meeting 19.10.2020](#meeting-3)

[Meeting 23.10.2020](#meeting-4)

[Meeting 30.10.2020](#meeting-5)

[Meeting 03.11.2020](#meeting-6)

[Meeting 06.11.2020](#meeting-7)

[Meeting 09.11.2020](#meeting-8)

[Meeting 11.11.2020](#meeting-9)

[Meeting 12.11.2020](#meeting-10)

[Meeting 05.03.2021](#meeting-11)

[Meeting 12.03.2021](#meeting-12)

[Meeting 17.03.2021](#meeting-13)


# <a name="meeting-1"></a> Meeting 14.10.2020
| **Verfasser** | Niklas Huber |
| --- | --- |
| **Team** | OPC UA Server Farm |
| **Teilnehmer** | Niclas Hörber, Niklas Huber, Nico Fischer, Kay Knoepfle, Phillip Förster, Daniel Zichler |

**Themen:**
- Vorgehensweise
  - In Thema OPC einlesen (jeder einzeln)
  - Wissen was in CRS, SRS und BC rein muss (jeder einzeln)
  - CRS aufstellen
- Teams Channel wo Infos für OPC
- Niklas soll der CRS-„Experte&quot; sein

**Status der Arbeit**: Informieren über das Thema

**Probleme**: keine

**Beschlüsse**: 
- Über CRS, SRS, BC und UPC informieren
- Teamschannel für UPC Informationen einrichten
- Alle relevanten Dateien in Teams hochladen

**Nächster vereinbarter Termin**: 16.10.2020

**Dauer**: Ca. 20 min 



# <a name="meeting-2"></a> Meeting 16.10.2020
| **Verfasser** | Niklas Huber |
| --- | --- |
| **Team** | OPC UA Server Farm |
| **Teilnehmer** | Niclas Hörber, Niklas Huber, Nico Fischer, Kay Knoepfle, Phillip Förster, Daniel Zichler |

**Themen:**
- Review zum MeetingMinutes File
- Ausfüllen des CRS (Goal)
- Weiteres Vorgehen planen (siehe Beschlüsse)

**Status der Arbeit**: Informieren über das Thema

**Probleme**: keine

**Beschlüsse**: 
- Goal in CRS einfügen
- Kay: Netzwerk multi IP Sache einlesen
- Phillip: CAEX 3.0 einlesen
- Niklas: CRS Thematik einlesen, Goal in CRS einfügen
- Niclas: Projektplan, BC einlesen
- Nico: grobe Anforderungen erarbeiten
- Daniel: OPC UA Client UA-Expert einlesen

**Nächster vereinbarter Termin**: 19.10.2020

**Dauer**: 1 Std



# <a name="meeting-3"></a> Meeting 19.10.2020
| **Verfasser** | Niklas Huber |
| --- | --- |
| **Team** | OPC UA Server Farm |
| **Teilnehmer** | Niclas Hörber, Niklas Huber, Nico Fischer, Kay Knoepfle, Phillip Förster, Daniel Zichler |

**Themen:**
- Files nach GIT umziehen
- Aktuelles CRS reviewed
- Was hat es mit dem BC auf sich
- Mehrere IP-Adressen fraglich
- CAEX
- Test Client

**Status der Arbeit**: CRS erstellen

**Probleme**:
- Projekt Ziel, Grund der Entwicklung und Zielgruppe unklar
- Mehrere IP-Adressen fraglich

**Beschlüsse**: 
- Niklas: 2 Product Environment erstellen
- Mail an Dozenten: Was muss alles in BC rein / Genauer Inhalt des BC / Projektziel, Grund der Entwicklung, Zielgruppe unklar
- Kai: Weiter mehrere IP-Adressen
- Nico: Files nach GIT umziehen

**Nächster vereinbarter Termin**: 23.10.2020

**Dauer**: 45 min



# <a name="meeting-4"></a> Meeting 23.10.2020
| **Verfasser** | Niklas Huber |
| --- | --- |
| **Team** | OPC UA Server Farm |
| **Teilnehmer** | Niclas Hörber, Niklas Huber, Nico Fischer, Kay Knoepfle, Phillip Förster, Daniel Zichler |

**Themen:**
- Neue Projektumgebung: Github
- Review zu CRS – Product Environment
- Review zum BC

**Status der Arbeit**: CRS erstellen

**Probleme**: Aktuell unbekanntes Abgabedatum für Dokumentation

**Beschlüsse**: 
- Jeder: Risiken fürs Projekt überlegen
- Niklas: CRS weitermachen
- Kay: Weiter in einarbeiten

**Nächster vereinbarter Termin**: 30.10.2020

**Dauer**: 1 Std



# <a name="meeting-5"></a> Meeting 30.10.2020
| **Verfasser** | Niklas Huber |
| --- | --- |
| **Team** | OPC UA Server Farm |
| **Teilnehmer** | Niclas Hörber, Niklas Huber, Nico Fischer, Kay Knoepfle, Phillip Förster, Daniel Zichler |

**Themen:**
- BC in Zusammenarbeit erstellen
    - Gant Chart
        - Aufgaben verteilen (Entwicklung)
            - Backend entwickeln
                - Umsetzung der Netzwerkkomponente (Mehrere Instanzen)
                - CAEX parser -> Backend muss CAEX Dateien einlesen können
                - Definieren & Implementierung der OPC UA Features
            - Definition des Konfigurationsdateiformats in CAEX 3.0
            - Definition von 10 aussagekräftigen Profilen
                - Welche Use Cases mit den Profilen abdecken
                - Basierend darauf die Profile erstellen
            - Testen
    - Risiko-Impact Analyse zusammen erstellt
- Weitere Vorgehensweise
- CRS besprochen
- Call mit Dozenten, um Fragen zu stellen

**Status der Arbeit**: Erstellen der Dokumente

**Probleme**: keine

**Beschlüsse**: 
- Jeder schreibt seinen Teil ins Wiki
- Phillipp probiert sich mal am SAS

**Nächster vereinbarter Termin**: 03.11.2020

**Dauer**: 1,5 Std



# <a name="meeting-6"></a> Meeting 03.11.2020
| **Verfasser** | Niklas Huber |
| --- | --- |
| **Team** | OPC UA Server Farm |
| **Teilnehmer** | Niclas Hörber, Niklas Huber, Nico Fischer, Kay Knoepfle, Phillip Förster, Daniel Zichler |

**Themen:**
- BC / Projektplan
    - Review im gesamten Team
    - Projektstrukturplaninhalt in CRS, SAS, SRS einarbeiten
- CRS
    - Review im gesamten Team
- SAS
    - Review im gesamten Team
- SRS
    - Review im gesamten Team
- Netzwerklayer von open62541 neu implementieren
    - Meeting mit Dozenten, um Problem zu lösen
    - Issue in open62541 Github öffnen
        - Müssen auf unterschiedlichen Ports arbeiten

**Status der Arbeit**: Erstellen der Dokumente

**Probleme**: Wie sollen wir Teile des SAS schon vor implementierung machen?

**Beschlüsse**: 
- Fragen: Muss im jetzigen Semester jedes Teammitglied ein Dokument haben?
- CRS, SRS, SAS weiter ausarbeiten
- Daniel fängt mit Präsentation an

**Nächster vereinbarter Termin**: 06.11.2020

**Dauer**: 1,5 Std



# <a name="meeting-7"></a> Meeting 06.11.2020
| **Verfasser** | Niklas Huber |
| --- | --- |
| **Team** | OPC UA Server Farm |
| **Teilnehmer** | Niclas Hörber, Niklas Huber, Nico Fischer, Kay Knoepfle, Phillip Förster, Daniel Zichler |

**Themen:**
- Weitere Vorgehensweise besprochen
    - CRS fertig machen
    - SRS fertig machen
    - SAS fertig machen
    - Präsentation erstellen
    - SRS und SAS in Wiki aufnehmen

**Status der Arbeit**: Erstellung/Überarbeitung der Dokumente

**Probleme**:

**Beschlüsse**: 
- Bis nächstes Meeting: Dokumente fertig
- Dann mit Präsentation beginnen

**Nächster vereinbarter Termin**: 09.11.2020

**Dauer**: 1 Std



# <a name="meeting-8"></a> Meeting 09.11.2020
| **Verfasser** | Niklas Huber |
| --- | --- |
| **Team** | OPC UA Server Farm |
| **Teilnehmer** | Niclas Hörber, Niklas Huber, Nico Fischer, Kay Knoepfle, Phillip Förster, Daniel Zichler |

**Themen:**
- Projektplan, BC, CRS, SRS und SAS im Team reviewed
- Präsentationstemplate erstellt
- Aufteilen der Präsentation


**Status der Arbeit**: Dokumentation abgeschlossen

**Probleme**:

**Beschlüsse**: 
- Jeder macht seinen Präsentationsteil
- Nico: SRS und SAS in Git Wiki

**Nächster vereinbarter Termin**: 11.11.2020

**Dauer**: 1,5 Std



# <a name="meeting-9"></a> Meeting 11.11.2020
| **Verfasser** | Niklas Huber |
| --- | --- |
| **Team** | OPC UA Server Farm |
| **Teilnehmer** | Niclas Hörber, Niklas Huber, Nico Fischer, Kay Knoepfle, Phillip Förster, Daniel Zichler |

**Themen:**
- Review zur Präsentation
- Review zum SRS und SAS in Git Wiki

**Status der Arbeit**: Vorbereitung auf Präsentation

**Probleme**:

**Beschlüsse**: 

**Nächster vereinbarter Termin**: 12.11.2020

**Dauer**: 1 Std



# <a name="meeting-10"></a> Meeting 12.11.2020
| **Verfasser** | Niklas Huber |
| --- | --- |
| **Team** | OPC UA Server Farm |
| **Teilnehmer** | Niclas Hörber, Niklas Huber, Nico Fischer, Kay Knoepfle, Phillip Förster, Daniel Zichler |

**Themen:**
- Nochmaliges Review zur Präsentation

**Status der Arbeit**: Vorbereitung auf Präsentation

**Probleme**:

**Beschlüsse**: SRS und SAS in Git Wiki

**Nächster vereinbarter Termin**: Präsentation in Vorlesung

**Dauer**: 1 Std

# <a name="meeting-11"></a> Meeting 05.03.2021
| **Verfasser** | Niklas Huber |
| --- | --- |
| **Team** | OPC UA Server Farm |
| **Teilnehmer** | Niclas Hörber, Niklas Huber, Nico Fischer, Kay Knoepfle, Phillip Förster, Daniel Zichler |

**Themen:**
- Stand des Projekts
    - Mit Coding starten
        - Bisherige Arbeit von Kay bekommen
    - CAEX 3.0 Parser
    - Open62541Stack
- Ausscheiden von Kay
    - Phillip wird zum Product Manager „befördert“

**Status der Arbeit**: Alle wieder auf aktuellen Stand bringen

**Probleme**: 
- Hauptentwickler hat Projektgruppe verlassen
- Versionsprobleme
- 
**Beschlüsse**: 
- Jeder liest alle bisherige Doku durch
- Jeder installiert WSL 2 / Linux

**Nächster vereinbarter Termin**: 12.03.2021

**Dauer**: 45 min



# <a name="meeting-12"></a> Meeting 12.03.2021
| **Verfasser** | Niklas Huber |
| --- | --- |
| **Team** | OPC UA Server Farm |
| **Teilnehmer** | Niclas Hörber, Niklas Huber, Nico Fischer, Kay Knoepfle, Phillip Förster, Daniel Zichler |

**Themen:** Weiteres Vorgehen (siehe Beschlüsse) / Nachbesprechung der 1. Vorlesung im 4. Semester

**Status der Arbeit**: Alle wieder auf aktuellen Stand bringen

**Probleme**:

**Beschlüsse**: 
- Niklas:
    - Git den Anforderungen des Dozenten anpassen
- Nico & Phillip:
    - Implementierung anfangen / informieren
- Daniel:
    - Vorlage seines Dokuments machen
- Niclas
    - Informieren was alles gemacht werden muss (Projektdoku, Abgabe, …)
- Projekt in aktueller Version (Alte Version verwerfen)

**Nächster vereinbarter Termin**:  17.03.2021

**Dauer**: 30 min



# <a name="meeting-13"></a> Meeting 17.03.2021
| **Verfasser** | Niklas Huber |
| --- | --- |
| **Team** | OPC UA Server Farm |
| **Teilnehmer** | Niclas Hörber, Niklas Huber, Nico Fischer, Kay Knoepfle, Phillip Förster, Daniel Zichler |

**Themen:** 
- a

**Status der Arbeit**:

**Probleme**:

**Beschlüsse**: 

**Nächster vereinbarter Termin**:

**Dauer**: