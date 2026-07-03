#pragma once
#include <SDL.h>
#include <memory>
#include <vector>
#include "Tastatur.hpp"
#include "LevelKarte.hpp"
#include "Spieler.hpp"
#include "Gegner.hpp"
#include "Stein.hpp"
#include "Bilder.hpp"

class Spiel {
private:
    static constexpr int WINDOW_WIDTH = 640;
    static constexpr int WINDOW_HEIGHT = 480;
    static constexpr int REQUIRED_CRYSTALS = 7;
    static constexpr float LEVEL_TIME_SECONDS = 90.0f;

    bool running = false;
    bool victory = false;
    bool gameOver = false;
    int lives = 3;
    int currentLevel = 1;
    float timeLeft = LEVEL_TIME_SECONDS;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Tastatur input;
    Bilder textures;
    LevelKarte map;
    std::unique_ptr<Spieler> player;
    std::vector<std::unique_ptr<Gegner>> enemies;
    std::vector<std::unique_ptr<Stein>> boulders;

    void verarbeiteEingaben();
    void aktualisiereSpiel(float deltaTime);
    void zeichneSpiel();
    void pruefeKollisionen();
    void verliereLeben();
    void starteNaechstesLevel();
    void zeichneAnzeige();
    bool ladeLevel(const std::string& path);

public:
    bool vorbereiten();
    void spielen();
    void beenden();
    ~Spiel();
};
