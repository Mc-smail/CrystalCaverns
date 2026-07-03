#pragma once
#include <string>
#include <vector>
#include <SDL.h>
#include "Feld.hpp"
#include "Datentypen.hpp"
#include "Bilder.hpp"

class LevelKarte {
private:
    std::vector<std::vector<Feld>> tiles;
    int width = 0;
    int height = 0;
    int tileSize = 32;
    Position2D playerStart{1, 1};
    std::vector<Position2D> enemyStarts;
    std::vector<Position2D> boulderStarts;

public:
    bool ladeAusDatei(const std::string& filename);
    void zeichnen(SDL_Renderer* renderer, const Bilder& textures) const;

    bool istImBereich(int x, int y) const;
    bool istBegehbar(int x, int y) const;
    Feld& getFeld(int x, int y);
    const Feld& getFeld(int x, int y) const;
    void setFeld(int x, int y, FeldTyp type);
    void oeffneAusgang();

    int getWidth() const;
    int getHeight() const;
    int getFeldGroesse() const;
    Position2D getSpielerStart() const;
    const std::vector<Position2D>& getGegnerStarts() const;
    const std::vector<Position2D>& getSteinStarts() const;
};
