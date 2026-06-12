# Crystal Caverns

Crystal Caverns ist ein kleines 2D-Retro-Spiel in **C++17** mit **SDL2**.
Der Spieler bewegt sich durch eine Höhle, sammelt Kristalle, vermeidet Gegner und fallende Steine und erreicht den Ausgang.

## Features

- SDL2-Fenster und Renderer
- Game Loop: Input → Update → Render
- Tilemap aus Textdatei
- Spielerbewegung mit WASD oder Pfeiltasten
- Kristalle sammeln
- Ausgang öffnet sich nach 3 Kristallen
- Gegner mit einfacher Bewegung
- fallende Steine
- Game Over und Victory-Zustand
- objektorientierte C++-Struktur

## Steuerung

- `W/A/S/D` oder Pfeiltasten: Spieler bewegen
- `R`: Level nach Sieg/Game Over neu starten
- `ESC`: Spiel beenden

## Level-Zeichen

| Zeichen | Bedeutung |
|---|---|
| `#` | Wand |
| `.` | Erde / begehbares Feld |
| `P` | Spielerstart |
| `C` | Kristall |
| `O` | Stein |
| `X` | Gegner |
| `E` | Ausgang |

## Build

### macOS mit Homebrew

```bash
brew install cmake sdl2
mkdir -p build
cd build
cmake ..
cmake --build .
cd ..
./build/CrystalCaverns
```

### Ubuntu/Kali/Debian

```bash
sudo apt update
sudo apt install -y build-essential cmake libsdl2-dev
mkdir -p build
cd build
cmake ..
cmake --build .
cd ..
./build/CrystalCaverns
```

## Projektstruktur

```text
CrystalCaverns/
├── CMakeLists.txt
├── README.md
├── assets/
│   └── levels/
│       └── level01.txt
├── include/
│   ├── Game.hpp
│   ├── TileMap.hpp
│   ├── Tile.hpp
│   ├── Entity.hpp
│   ├── Player.hpp
│   ├── Enemy.hpp
│   ├── Boulder.hpp
│   └── InputManager.hpp
└── src/
    ├── main.cpp
    ├── Game.cpp
    ├── TileMap.cpp
    ├── Tile.cpp
    ├── Entity.cpp
    ├── Player.cpp
    ├── Enemy.cpp
    ├── Boulder.cpp
    └── InputManager.cpp
```

## Bezug zur Vorlesung

Das Projekt nutzt zentrale Inhalte aus 2D Game Development und C++:

- SDL Event Handling
- Keyboard State
- Game Loop
- Tilemaps
- einfache Kollisionen
- Klassen und Vererbung
- Polymorphismus über `Entity`
- moderne Speicherverwaltung mit `std::unique_ptr`
