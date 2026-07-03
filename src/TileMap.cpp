#include "TileMap.hpp"
#include <fstream>
#include <iostream>

bool TileMap::ladeAusDatei(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open level: " << filename << "\n";
        return false;
    }

    tiles.clear();
    enemyStarts.clear();
    boulderStarts.clear();

    std::string line;
    int y = 0;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::vector<Tile> row;
        for (int x = 0; x < static_cast<int>(line.size()); ++x) {
            char c = line[x];
            switch (c) {
                case '#': row.emplace_back(TileType::Wall); break;
                case '.': row.emplace_back(TileType::Dirt); break;
                case 'C': row.emplace_back(TileType::Crystal); break;
                case 'O':
                    row.emplace_back(TileType::Empty);
                    boulderStarts.push_back({x, y});
                    break;
                case 'X':
                    row.emplace_back(TileType::Empty);
                    enemyStarts.push_back({x, y});
                    break;
                case 'P':
                    row.emplace_back(TileType::Empty);
                    playerStart = {x, y};
                    break;
                case 'E': row.emplace_back(TileType::ExitClosed); break;
                default: row.emplace_back(TileType::Empty); break;
            }
        }
        tiles.push_back(row);
        ++y;
    }

    height = static_cast<int>(tiles.size());
    width = height > 0 ? static_cast<int>(tiles.front().size()) : 0;
    return width > 0 && height > 0;
}

void TileMap::zeichnen(SDL_Renderer* renderer, const TextureManager& textures) const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            SDL_Rect rect{x * tileSize, y * tileSize, tileSize, tileSize};
            const Tile& tile = tiles[y][x];

            const char* textureId = "empty";
            switch (tile.getTyp()) {
                case TileType::Wall:       textureId = "wall"; break;
                case TileType::Dirt:       textureId = "dirt"; break;
                case TileType::Crystal:    textureId = "crystal"; break;
                case TileType::Boulder:    textureId = "boulder"; break;
                case TileType::ExitClosed: textureId = "exit_closed"; break;
                case TileType::ExitOpen:   textureId = "exit_open"; break;
                case TileType::Empty:      textureId = "empty"; break;
            }

            SDL_Texture* texture = textures.getTextur(textureId);
            if (texture) {
                SDL_RenderCopy(renderer, texture, nullptr, &rect);
            } else {
                SDL_Color color = tile.farbe();
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_RenderFillRect(renderer, &rect);
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 70);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

bool TileMap::istImBereich(int x, int y) const {
    return y >= 0 && y < height && x >= 0 && x < width;
}

bool TileMap::istBegehbar(int x, int y) const {
    return istImBereich(x, y) && tiles[y][x].istBegehbar();
}

Tile& TileMap::getFeld(int x, int y) { return tiles[y][x]; }
const Tile& TileMap::getFeld(int x, int y) const { return tiles[y][x]; }
void TileMap::setFeld(int x, int y, TileType type) { if (istImBereich(x,y)) tiles[y][x].setTyp(type); }

void TileMap::oeffneAusgang() {
    for (auto& row : tiles) {
        for (auto& tile : row) {
            if (tile.getTyp() == TileType::ExitClosed) tile.setTyp(TileType::ExitOpen);
        }
    }
}

int TileMap::getWidth() const { return width; }
int TileMap::getHeight() const { return height; }
int TileMap::getFeldGroesse() const { return tileSize; }
Vector2i TileMap::getSpielerStart() const { return playerStart; }
const std::vector<Vector2i>& TileMap::getGegnerStarts() const { return enemyStarts; }
const std::vector<Vector2i>& TileMap::getSteinStarts() const { return boulderStarts; }
