# Simulator Eiswasserspeicher
Der Simulator unterteilt sich in zwei Komponenten, der ControlClient und der Simulator.

## ControlClient
Der ControlClient dient als Verbindung zum Simulator um Kommandos abzusetzen. Drei Möglichkeiten stehen dabei zur Auswahl:

1. Ladevorgang umschalten
2. Kühlvorgang umschalten
3. Verlassen

Der Simulator lädt während des Ladevorgangs seine Eisreserven voll. Währendessen kann auch der Kühlvorgang angestoßen werden.
Der ControlClient muss mit der `parameters.ini` als Kommandozeilenargument gestartet werden, welche die Verbdinungsdaten zum Simulator enthält. 

## Simulator
Der Simulator teilt sich in mehrere kleinere Funktionseinheiten auf. Auf der einen Seite stehen die organisatorischen Teile, die das Logging, die Verbindung zum Client und das Laden der Parameter verwalten. Auf der anderen Seite steht der Simulator, welcher wieder in kleinere Einheiten aufgeteilt ist:

1. Simulator, als übergeordnete Einheit
2. Reservoir, als Speicher für das Eis und Koordinator (enthält Pumpen und S0-Schnittstelle)
3. SNull

Der Simulator führt die Simulation in einem eigenen Thread aus und reagiert auf die Kommandos, die vom Client gesendet werden. 

### Speicher
Das Reservoir, der eigentliche Eiswasserspeicher, setzt das mathematische Modell um und führt in der `step` Methode entweder das Laden oder Kühlen um. Dies würde darüber entschieden, ob die Pumpen an sind, geladen werden kann (Zeitsteuerung 12-16 Uhr) oder genug Eis im Speicher ist. Das Laden und Kühlen findet den den dafür vorgesehen Methoden, `load` und `cool` statt. Am Ende einer dieser beiden Methoden wird die Leistung mit der S0-Schnittstelle übertragen.

### S0-Schnittstelle
Die S0-Schnittstelle ist die letzte wichtige Komponente. Sie dient als Datenübertragungsschnittstelle für externe Geräte, um die Leistung des Eiswasserspeicher mitzuteilen. Die S0-Schnittstelle setzt die Bibliothek [wiringPi](http://wiringpi.com) vorraus, damit die I/O Pins des RapsberryPis angesprochen werden können. Damit eine galvanische Trennung zwischen Simulator und externen Geräten stattfinden kann, muss ein Optokoppler eingesetzt werden. Nachfolgendes Schema zeigt einen groben Aufbau davon, welcher einen Arduino als Datenlogger einsetzt.

![Schematischer Aufbau](http://i.imgur.com/ONr5beX.png?3)

Der Optopkoppler und die nötigen Widerstände müssen je nach Einsatzzweck angepasst werden. In diesem Aufbau wurde der Optokoppler [Kingbright KB 817 DIP-4](https://www.conrad.de/de/optokoppler-typ-kb-kingbright-kb-817-dip-4-ausfuehrung-single-transistor-type-140363.html) verwendet. Das Programm, das der Arduino verwendet um die Signal zu empfangen, ist [hier](https://gist.github.com/tpohl90/612289bbebd075a6a239) zu finden.


## Ablauf
Ein typischer Ablauf für eine Simulation könnte ungefähr so aussehen:

1. 05:00 Uhr - Einschalten der Pumpen, Starten des Kühlvorgangs
2. 06:33 Uhr - Speicher ist leer
3. 08:30 Uhr - Ladevorgang anschalten
4. 12:00 Uhr - Speicher wird geladen
5. 16:00 Uhr - Laden stoppen, Speicher zu ungefähr 2/3 voll
6. 16:30 Uhr - Starten des Kühlvorgangs
7. 17:30 Uhr - Speicher ist leer

