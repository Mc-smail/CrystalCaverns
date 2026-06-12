#include "Game.hpp"
#include <iostream>
#include <string>

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow(
        "Crystal Caverns",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << "\n";
        return false;
    }

    textures.setRenderer(renderer);
    textures.load("empty", "assets/sprites/empty.bmp");
    textures.load("dirt", "assets/sprites/dirt.bmp");
    textures.load("wall", "assets/sprites/wall.bmp");
    textures.load("crystal", "assets/sprites/crystal.bmp");
    textures.load("boulder", "assets/sprites/boulder.bmp");
    textures.load("player", "assets/sprites/player.bmp");
    textures.load("enemy", "assets/sprites/enemy.bmp");
    textures.load("exit_closed", "assets/sprites/exit_closed.bmp");
    textures.load("exit_open", "assets/sprites/exit_open.bmp");

    if (!loadLevel("assets/levels/level01.txt")) {
        return false;
    }

    running = true;
    return true;
}

bool Game::loadLevel(const std::string& path) {
    if (!map.loadFromFile(path)) {
        return false;
    }

    Vector2i start = map.getPlayerStart();
    player = std::make_unique<Player>(start.x, start.y, textures.get("player"));

    enemies.clear();
    for (const auto& pos : map.getEnemyStarts()) {
        enemies.push_back(std::make_unique<Enemy>(pos.x, pos.y, textures.get("enemy")));
    }

    boulders.clear();
    for (const auto& pos : map.getBoulderStarts()) {
        boulders.push_back(std::make_unique<Boulder>(pos.x, pos.y, textures.get("boulder")));
    }

    victory = false;
    gameOver = false;
    timeLeft = LEVEL_TIME_SECONDS;
    return true;
}

void Game::run() {
    Uint64 previous = SDL_GetPerformanceCounter();

    while (running) {
        Uint64 current = SDL_GetPerformanceCounter();
        float deltaTime = static_cast<float>(current - previous) / static_cast<float>(SDL_GetPerformanceFrequency());
        previous = current;

        handleEvents();
        update(deltaTime);
        render();
    }
}

void Game::handleEvents() {
    SDL_Event event{};
    while (SDL_PollEvent(&event)) {
        input.handleEvent(event);
    }
    input.update();
    if (input.shouldQuit()) running = false;

    if ((victory || gameOver) && input.isKeyPressed(SDL_SCANCODE_R)) {
        lives = 3;
        currentLevel = 1;
        loadLevel("assets/levels/level01.txt");
    }

    if (victory && input.isKeyPressed(SDL_SCANCODE_N)) {
        nextLevel();
    }
}

void Game::update(float deltaTime) {
    if (!player || victory || gameOver) return;

    timeLeft -= deltaTime;
    if (timeLeft <= 0.0f) {
        loseLife();
        return;
    }

    player->handleInput(input, map);
    player->update(deltaTime, map);

    for (auto& boulder : boulders) boulder->update(deltaTime, map);
    for (auto& enemy : enemies) enemy->update(deltaTime, map);

    if (player->getCrystals() >= REQUIRED_CRYSTALS) {
        map.openExit();
    }

    const auto p = player->getPosition();
    if (map.getTile(p.x, p.y).getType() == TileType::ExitOpen) {
        if (currentLevel >= 2) {
            victory = true;
        } else {
            nextLevel();
        }
        return;
    }

    checkCollisions();
}

void Game::checkCollisions() {
    const auto p = player->getPosition();

    for (const auto& enemy : enemies) {
        if (enemy->getPosition().x == p.x && enemy->getPosition().y == p.y) {
            loseLife();
            return;
        }
    }

    for (const auto& boulder : boulders) {
        const auto b = boulder->getPosition();
        if (b.x == p.x && b.y == p.y && boulder->isFalling()) {
            loseLife();
            return;
        }
    }
}


void Game::loseLife() {
    --lives;
    if (lives <= 0) {
        gameOver = true;
        return;
    }

    const std::string path = currentLevel == 1 ? "assets/levels/level01.txt" : "assets/levels/level02.txt";
    loadLevel(path);
}

void Game::nextLevel() {
    if (currentLevel == 1) {
        currentLevel = 2;
        loadLevel("assets/levels/level02.txt");
    } else {
        victory = true;
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 10, 12, 20, 255);
    SDL_RenderClear(renderer);

    map.render(renderer, textures);
    for (const auto& boulder : boulders) boulder->render(renderer, map.getTileSize());
    for (const auto& enemy : enemies) enemy->render(renderer, map.getTileSize());
    if (player) player->render(renderer, map.getTileSize());

    drawHud();
    SDL_RenderPresent(renderer);
}

void Game::drawHud() {
    SDL_Rect hud{0, WINDOW_HEIGHT - 32, WINDOW_WIDTH, 32};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
    SDL_RenderFillRect(renderer, &hud);

    // Crystal counter: cyan boxes.
    int count = player ? player->getCrystals() : 0;
    for (int i = 0; i < REQUIRED_CRYSTALS; ++i) {
        SDL_Rect gem{12 + i * 22, WINDOW_HEIGHT - 24, 15, 15};
        if (i < count) SDL_SetRenderDrawColor(renderer, 60, 220, 255, 255);
        else SDL_SetRenderDrawColor(renderer, 45, 55, 70, 255);
        SDL_RenderFillRect(renderer, &gem);
    }

    // Lives: yellow boxes.
    for (int i = 0; i < 3; ++i) {
        SDL_Rect life{210 + i * 24, WINDOW_HEIGHT - 24, 16, 16};
        if (i < lives) SDL_SetRenderDrawColor(renderer, 255, 220, 70, 255);
        else SDL_SetRenderDrawColor(renderer, 70, 60, 40, 255);
        SDL_RenderFillRect(renderer, &life);
    }

    // Timer bar: green -> red as time runs out.
    int barWidth = static_cast<int>((timeLeft / LEVEL_TIME_SECONDS) * 180.0f);
    if (barWidth < 0) barWidth = 0;
    SDL_Rect timerBack{350, WINDOW_HEIGHT - 23, 180, 14};
    SDL_SetRenderDrawColor(renderer, 45, 55, 70, 255);
    SDL_RenderFillRect(renderer, &timerBack);
    SDL_Rect timer{350, WINDOW_HEIGHT - 23, barWidth, 14};
    if (timeLeft > 30.0f) SDL_SetRenderDrawColor(renderer, 40, 220, 90, 255);
    else SDL_SetRenderDrawColor(renderer, 230, 70, 55, 255);
    SDL_RenderFillRect(renderer, &timer);

    if (victory) {
        SDL_Rect box{180, 170, 280, 90};
        SDL_SetRenderDrawColor(renderer, 30, 180, 80, 230);
        SDL_RenderFillRect(renderer, &box);
    } else if (gameOver) {
        SDL_Rect box{180, 170, 280, 90};
        SDL_SetRenderDrawColor(renderer, 190, 40, 60, 230);
        SDL_RenderFillRect(renderer, &box);
    }
}

void Game::quit() {
    running = false;
}

Game::~Game() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}
