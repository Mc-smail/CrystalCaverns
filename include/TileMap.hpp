#pragma once
#include <string>
#include <vector>
#include <SDL.h>
#include "Tile.hpp"
#include "Types.hpp"
#include "TextureManager.hpp"

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
    bool ladeAusDatei(const std::string& filename);
    void zeichnen(SDL_Renderer* renderer, const TextureManager& textures) const;

    bool istImBereich(int x, int y) const;
    bool istBegehbar(int x, int y) const;
    Tile& getFeld(int x, int y);
    const Tile& getFeld(int x, int y) const;
    void setFeld(int x, int y, TileType type);
    void oeffneAusgang();

    int getWidth() const;
    int getHeight() const;
    int getFeldGroesse() const;
    Vector2i getSpielerStart() const;
    const std::vector<Vector2i>& getGegnerStarts() const;
    const std::vector<Vector2i>& getSteinStarts() const;
};
