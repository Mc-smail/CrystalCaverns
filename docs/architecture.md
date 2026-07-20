# Architecture Notes

The game is split into small classes:

- `Spiel` coordinates the main loop and level state
- `Tastatur` handles input
- `Bilder` manages textures
- `LevelKarte` owns the tile map
- `Figur` is the base class for moving entities
- `Spieler`, `Gegner` and `Stein` implement concrete behavior
