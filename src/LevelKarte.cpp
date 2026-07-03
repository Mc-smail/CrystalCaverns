#include "LevelKarte.hpp"
#include <fstream>
#include <iostream>

bool LevelKarte::ladeAusDatei(const std::string& filename) {
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
        std::vector<Feld> row;
        for (int x = 0; x < static_cast<int>(line.size()); ++x) {
            char c = line[x];
            switch (c) {
                case '#': row.emplace_back(FeldTyp::Wall); break;
                case '.': row.emplace_back(FeldTyp::Dirt); break;
                case 'C': row.emplace_back(FeldTyp::Crystal); break;
                case 'O':
                    row.emplace_back(FeldTyp::Empty);
                    boulderStarts.push_back({x, y});
                    break;
                case 'X':
                    row.emplace_back(FeldTyp::Empty);
                    enemyStarts.push_back({x, y});
                    break;
                case 'P':
                    row.emplace_back(FeldTyp::Empty);
                    playerStart = {x, y};
                    break;
                case 'E': row.emplace_back(FeldTyp::ExitClosed); break;
                default: row.emplace_back(FeldTyp::Empty); break;
            }
        }
        tiles.push_back(row);
        ++y;
    }

    height = static_cast<int>(tiles.size());
    width = height > 0 ? static_cast<int>(tiles.front().size()) : 0;
    return width > 0 && height > 0;
}

void LevelKarte::zeichnen(SDL_Renderer* renderer, const Bilder& textures) const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            SDL_Rect rect{x * tileSize, y * tileSize, tileSize, tileSize};
            const Feld& tile = tiles[y][x];

            const char* textureId = "empty";
            switch (tile.getTyp()) {
                case FeldTyp::Wall:       textureId = "wall"; break;
                case FeldTyp::Dirt:       textureId = "dirt"; break;
                case FeldTyp::Crystal:    textureId = "crystal"; break;
                case FeldTyp::Stein:    textureId = "boulder"; break;
                case FeldTyp::ExitClosed: textureId = "exit_closed"; break;
                case FeldTyp::ExitOpen:   textureId = "exit_open"; break;
                case FeldTyp::Empty:      textureId = "empty"; break;
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

bool LevelKarte::istImBereich(int x, int y) const {
    return y >= 0 && y < height && x >= 0 && x < width;
}

bool LevelKarte::istBegehbar(int x, int y) const {
    return istImBereich(x, y) && tiles[y][x].istBegehbar();
}

Feld& LevelKarte::getFeld(int x, int y) { return tiles[y][x]; }
const Feld& LevelKarte::getFeld(int x, int y) const { return tiles[y][x]; }
void LevelKarte::setFeld(int x, int y, FeldTyp type) { if (istImBereich(x,y)) tiles[y][x].setTyp(type); }

void LevelKarte::oeffneAusgang() {
    for (auto& row : tiles) {
        for (auto& tile : row) {
            if (tile.getTyp() == FeldTyp::ExitClosed) tile.setTyp(FeldTyp::ExitOpen);
        }
    }
}

int LevelKarte::getWidth() const { return width; }
int LevelKarte::getHeight() const { return height; }
int LevelKarte::getFeldGroesse() const { return tileSize; }
Position2D LevelKarte::getSpielerStart() const { return playerStart; }
const std::vector<Position2D>& LevelKarte::getGegnerStarts() const { return enemyStarts; }
const std::vector<Position2D>& LevelKarte::getSteinStarts() const { return boulderStarts; }
