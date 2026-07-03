#pragma once
#include "Figur.hpp"

class Gegner : public Figur {
private:
    Richtung direction = Richtung::Left;
    float moveTimer = 0.0f;

public:
    Gegner(int x, int y, SDL_Texture* texture = nullptr);
    void aktualisieren(float deltaTime, LevelKarte& map) override;
};
