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

    TileType getType() const;
    void setType(TileType newType);

    bool isSolid() const;
    bool isWalkable() const;
    bool isCollectible() const;
    SDL_Color color() const;
};
