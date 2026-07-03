#include "Spiel.hpp"

int main(int, char**) {
    Spiel game;
    if (!game.vorbereiten()) {
        return 1;
    }
    game.spielen();
    return 0;
}
