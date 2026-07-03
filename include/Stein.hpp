#pragma once
#include "Figur.hpp"

class Stein : public Figur {
private:
    float fallTimer = 0.0f;
    bool falling = false;

public:
    Stein(int x, int y, SDL_Texture* texture = nullptr);
    bool faelltGerade() const;
    void aktualisieren(float deltaTime, LevelKarte& map) override;
};
