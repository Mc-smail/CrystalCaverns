#pragma once
#include <string>
#include <vector>
#include <SDL.h>
#include "Tile.hpp"
#include "Types.hpp"

class TileMap {
private:
    std::vector<std::vector<Tile>> tiles;
    int width = 0;
    int height = 0;
    int tileSize = 32;
    Vector2i playerStart{1, 1};
    std::vector<Vector2i> enemyStarts;
    std::vector<Vector2i> boulderStarts;

public:
    bool loadFromFile(const std::string& filename);
    void render(SDL_Renderer* renderer) const;

    bool inBounds(int x, int y) const;
    bool isWalkable(int x, int y) const;
    Tile& getTile(int x, int y);
    const Tile& getTile(int x, int y) const;
    void setTile(int x, int y, TileType type);
    void openExit();

    int getWidth() const;
    int getHeight() const;
    int getTileSize() const;
    Vector2i getPlayerStart() const;
    const std::vector<Vector2i>& getEnemyStarts() const;
    const std::vector<Vector2i>& getBoulderStarts() const;
};
