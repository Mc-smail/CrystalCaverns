#pragma once
#include "Figur.hpp"
#include "Tastatur.hpp"

class Spieler : public Figur {
private:
    int crystals = 0;
    float moveCooldown = 0.0f;

public:
    Spieler(int x, int y, SDL_Texture* texture = nullptr);
    void verarbeiteEingabe(const Tastatur& input, LevelKarte& map);
    void bewege(Richtung direction, LevelKarte& map);
    void sammleFeld(LevelKarte& map);
    int getKristalle() const;
    void aktualisieren(float deltaTime, LevelKarte& map) override;
};
