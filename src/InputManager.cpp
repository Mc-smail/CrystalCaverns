#include "InputManager.hpp"

void InputManager::aktualisiereTastatur() {
    SDL_PumpEvents();
    keyboardState = SDL_GetKeyboardState(nullptr);
}

void InputManager::verarbeiteEvent(const SDL_Event& event) {
    if (event.type == SDL_QUIT) {
        quitRequested = true;
    }
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        quitRequested = true;
    }
}

bool InputManager::tasteGedrueckt(SDL_Scancode key) const {
    return keyboardState && keyboardState[key];
}

bool InputManager::sollBeenden() const {
    return quitRequested;
}
