#include "Tastatur.hpp"

void Tastatur::aktualisiereTastatur() {
    SDL_PumpEvents();
    keyboardState = SDL_GetKeyboardState(nullptr);
}

void Tastatur::verarbeiteEvent(const SDL_Event& event) {
    if (event.type == SDL_QUIT) {
        quitRequested = true;
    }
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        quitRequested = true;
    }
}

bool Tastatur::tasteGedrueckt(SDL_Scancode key) const {
    return keyboardState && keyboardState[key];
}

bool Tastatur::sollBeenden() const {
    return quitRequested;
}
