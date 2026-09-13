# 2D Jump and Run in C mit SDL2

Ein kleines 2D-Jump-and-Run in **C** mit **SDL2**.

## Projektstruktur

```text
project/
├── Makefile
├── README.md
├── include/
│   ├── game.h
│   ├── player.h
│   ├── world.h
│   ├── physics.h
│   ├── collision.h
│   └── config.h
└── src/
    ├── main.c
    ├── game.c
    ├── player.c
    ├── world.c
    ├── physics.c
    └── collision.c
```

## Aufbau

- **main.c** – startet und beendet das Spiel.
- **game.c** – Game Loop, Events, Update und Rendering.
- **player.c** – Input, Springen und Double Jump.
- **world.c** – speichert Boden, Plattformen und andere Map-Objekte.
- **physics.c** – Gravitation, Bewegung und Kollisionsauflösung.
- **collision.c** – prüft Rechteck-Kollisionen.
- **config.h** – allgemeine Konstanten.

## Datenstruktur

Das `Game` besitzt den aktuellen Spielzustand:

```text
Game
├── Player
└── World
    └── WorldObject[]
```

Die World speichert alle festen Map-Objekte in einem Array.  
Der Boden ist dabei kein Sonderfall, sondern einfach ein großes Rechteck.

## Ablauf pro Frame

```text
Input
↓
Player-Logik
↓
Physics
↓
Collision
↓
Rendering
```

Für die Physik werden X- und Y-Bewegung getrennt behandelt:

```text
Gravitation
X bewegen → X-Kollisionen lösen
Y bewegen → Y-Kollisionen lösen
```

Dadurch sind Kollisionen mit Wänden und Plattformen einfacher zu behandeln.

## Kollisionen

Momentan werden einfache **AABB-Rechteckkollisionen** verwendet.

`collision.c` prüft nur, ob sich Rechtecke überschneiden.  
`physics.c` entscheidet danach, wie der Spieler korrigiert wird.

Beispiel beim Landen:

```text
velocity_y = 0
on_ground = true
```

## Kompilieren

```bash
make
```

Starten:

```bash
make run
```

Aufräumen:

```bash
make clean
```

## Ziel

Die Struktur soll später einfach erweitert werden können, zum Beispiel um:

- Gegner
- mehrere Levels
- Texturen und Animationen
- Kamera
- Collectibles
- bewegliche Plattformen
