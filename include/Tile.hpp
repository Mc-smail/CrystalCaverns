#pragma once
#include <SDL.h>

enum class TileType {
    Empty,
    Wall,
    Dirt,
    Crystal,
    Boulder,
    ExitClosed,
    ExitOpen
};

class Tile {
private:
    TileType type = TileType::Empty;

public:
    Tile() = default;
    explicit Tile(TileType type);

    TileType getTyp() const;
    void setTyp(TileType newType);

    bool istFest() const;
    bool istBegehbar() const;
    bool istSammelbar() const;
    SDL_Color farbe() const;
};
