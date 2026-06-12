#pragma once
#include <SDL.h>
#include <memory>
#include <vector>
#include "InputManager.hpp"
#include "TileMap.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Boulder.hpp"
#include "TextureManager.hpp"

class Game {
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
    InputManager input;
    TextureManager textures;
    TileMap map;
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Boulder>> boulders;

    void handleEvents();
    void update(float deltaTime);
    void render();
    void checkCollisions();
    void loseLife();
    void nextLevel();
    void drawHud();
    bool loadLevel(const std::string& path);

public:
    bool init();
    void run();
    void quit();
    ~Game();
};
