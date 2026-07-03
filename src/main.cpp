#include "Game.hpp"

int main(int, char**) {
    Game game;
    if (!game.vorbereiten()) {
        return 1;
    }
    game.spielen();
    return 0;
}
