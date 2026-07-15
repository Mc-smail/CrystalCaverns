#include "Spiel.hpp"
#include <iostream>
#include <string>

bool Spiel::vorbereiten() {
    //SDL für Fenster und Grafik benutzen.
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow(
        "Crystal Caverns",
        SDL_WINDOWPOS_CENTERED, // Werte stehen in Spiel.hpp
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
    textures.ladeTextur("empty", "assets/sprites/empty.bmp");
    textures.ladeTextur("dirt", "assets/sprites/dirt.bmp");
    textures.ladeTextur("wall", "assets/sprites/wall.bmp");
    textures.ladeTextur("crystal", "assets/sprites/crystal.bmp");
    textures.ladeTextur("boulder", "assets/sprites/boulder.bmp");
    textures.ladeTextur("player", "assets/sprites/player.bmp");
    textures.ladeTextur("enemy", "assets/sprites/enemy.bmp");
    textures.ladeTextur("exit_closed", "assets/sprites/exit_closed.bmp");
    textures.ladeTextur("exit_open", "assets/sprites/exit_open.bmp");

    if (!ladeLevel("assets/levels/level01.txt")) {
        return false;
    }

    running = true;
    return true;
}

bool Spiel::ladeLevel(const std::string& path) {
    if (!map.ladeAusDatei(path)) {
        return false;
    }

    Position2D start = map.getSpielerStart();
    player = std::make_unique<Spieler>(start.x, start.y, textures.getTextur("player"));

    enemies.clear();
    for (const auto& pos : map.getGegnerStarts()) {
        enemies.push_back(std::make_unique<Gegner>(pos.x, pos.y, textures.getTextur("enemy")));
    }

    boulders.clear();
    for (const auto& pos : map.getSteinStarts()) {
        boulders.push_back(std::make_unique<Stein>(pos.x, pos.y, textures.getTextur("boulder")));
    }

    victory = false;
    gameOver = false;
    timeLeft = LEVEL_TIME_SECONDS;
    return true;
}

void Spiel::spielen() {
    Uint64 previous = SDL_GetPerformanceCounter();

    while (running) {
        Uint64 current = SDL_GetPerformanceCounter();
        float deltaTime = static_cast<float>(current - previous) / static_cast<float>(SDL_GetPerformanceFrequency());
        previous = current;

        verarbeiteEingaben();
        aktualisiereSpiel(deltaTime);
        zeichneSpiel();
    }
}

void Spiel::verarbeiteEingaben() {
    SDL_Event event{};
    while (SDL_PollEvent(&event)) {
        input.verarbeiteEvent(event);
    }
    input.aktualisiereTastatur();
    if (input.sollBeenden()) running = false;

    if ((victory || gameOver) && input.tasteGedrueckt(SDL_SCANCODE_R)) {
        lives = 3;
        currentLevel = 1;
        ladeLevel("assets/levels/level01.txt");
    }

    if (victory && input.tasteGedrueckt(SDL_SCANCODE_N)) {
        starteNaechstesLevel();
    }
}

void Spiel::aktualisiereSpiel(float deltaTime) {
    if (!player || victory || gameOver) return;

    timeLeft -= deltaTime;
    if (timeLeft <= 0.0f) {
        verliereLeben();
        return;
    }

    player->verarbeiteEingabe(input, map);
    player->aktualisieren(deltaTime, map);

    for (auto& boulder : boulders) boulder->aktualisieren(deltaTime, map);
    for (auto& enemy : enemies) enemy->aktualisieren(deltaTime, map);

    if (player->getKristalle() >= REQUIRED_CRYSTALS) {
        map.oeffneAusgang();
    }

    const auto p = player->getPosition();
    if (map.getFeld(p.x, p.y).getTyp() == FeldTyp::ExitOpen) {
        if (currentLevel >= 2) {
            victory = true;
        } else {
            starteNaechstesLevel();
        }
        return;
    }

    pruefeKollisionen();
}

void Spiel::pruefeKollisionen() {
    const auto p = player->getPosition();

    for (const auto& enemy : enemies) {
        if (enemy->getPosition().x == p.x && enemy->getPosition().y == p.y) {
            verliereLeben();
            return;
        }
    }

    for (const auto& boulder : boulders) {
        const auto b = boulder->getPosition();
        if (b.x == p.x && b.y == p.y && boulder->faelltGerade()) {
            verliereLeben();
            return;
        }
    }
}

void Spiel::verliereLeben() {
    --lives;
    if (lives <= 0) {
        gameOver = true;
        return;
    }

    const std::string path = currentLevel == 1 ? "assets/levels/level01.txt" : "assets/levels/level02.txt";
    ladeLevel(path);
}

void Spiel::starteNaechstesLevel() {
    if (currentLevel == 1) {
        currentLevel = 2;
        ladeLevel("assets/levels/level02.txt");
    } else {
        victory = true;
    }
}

void Spiel::zeichneSpiel() {
    SDL_SetRenderDrawColor(renderer, 10, 12, 20, 255);
    SDL_RenderClear(renderer);

    map.zeichnen(renderer, textures);
    for (const auto& boulder : boulders) boulder->zeichnen(renderer, map.getFeldGroesse());
    for (const auto& enemy : enemies) enemy->zeichnen(renderer, map.getFeldGroesse());
    if (player) player->zeichnen(renderer, map.getFeldGroesse());

    zeichneAnzeige();
    SDL_RenderPresent(renderer);
}

void Spiel::zeichneAnzeige() {
    SDL_Rect hud{0, WINDOW_HEIGHT - 32, WINDOW_WIDTH, 32};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
    SDL_RenderFillRect(renderer, &hud);

    int count = player ? player->getKristalle() : 0;
    for (int i = 0; i < REQUIRED_CRYSTALS; ++i) {
        SDL_Rect gem{12 + i * 22, WINDOW_HEIGHT - 24, 15, 15};
        if (i < count) SDL_SetRenderDrawColor(renderer, 60, 220, 255, 255);
        else SDL_SetRenderDrawColor(renderer, 45, 55, 70, 255);
        SDL_RenderFillRect(renderer, &gem);
    }

    for (int i = 0; i < 3; ++i) {
        SDL_Rect life{210 + i * 24, WINDOW_HEIGHT - 24, 16, 16};
        if (i < lives) SDL_SetRenderDrawColor(renderer, 255, 220, 70, 255);
        else SDL_SetRenderDrawColor(renderer, 70, 60, 40, 255);
        SDL_RenderFillRect(renderer, &life);
    }

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

void Spiel::beenden() {
    running = false;
}

Spiel::~Spiel() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}
