#include "Tile.hpp"

Tile::Tile(TileType type) : type(type) {}

TileType Tile::getType() const { return type; }
void Tile::setType(TileType newType) { type = newType; }

bool Tile::isSolid() const {
    return type == TileType::Wall || type == TileType::Boulder || type == TileType::ExitClosed;
}

bool Tile::isWalkable() const {
    return type == TileType::Empty || type == TileType::Dirt || type == TileType::Crystal || type == TileType::ExitOpen;
}

bool Tile::isCollectible() const {
    return type == TileType::Crystal;
}

SDL_Color Tile::color() const {
    switch (type) {
        case TileType::Wall:       return {70, 70, 90, 255};
        case TileType::Dirt:       return {116, 74, 38, 255};
        case TileType::Crystal:    return {60, 220, 255, 255};
        case TileType::Boulder:    return {130, 130, 130, 255};
        case TileType::ExitClosed: return {120, 40, 160, 255};
        case TileType::ExitOpen:   return {40, 220, 90, 255};
        case TileType::Empty:      return {15, 18, 28, 255};
    }
    return {255, 0, 255, 255};
}
