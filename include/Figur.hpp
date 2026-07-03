#pragma once
#include <SDL.h>
#include "Datentypen.hpp"
#include "LevelKarte.hpp"

class Figur {
protected:
    Position2D position;
    SDL_Color renderColor{255,255,255,255};
    SDL_Texture* texture = nullptr;
    bool alive = true;

public:
    Figur(int x, int y, SDL_Color color, SDL_Texture* texture = nullptr);
    virtual ~Figur() = default;

    virtual void aktualisieren(float deltaTime, LevelKarte& map) = 0;
    virtual void zeichnen(SDL_Renderer* renderer, int tileSize) const;

    Position2D getPosition() const;
    SDL_Rect getHitbox(int tileSize) const;
    bool isAlive() const;
    void kill();
};
