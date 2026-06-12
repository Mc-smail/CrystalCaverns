#include "InputManager.hpp"

void InputManager::update() {
    SDL_PumpEvents();
    keyboardState = SDL_GetKeyboardState(nullptr);
}

void InputManager::handleEvent(const SDL_Event& event) {
    if (event.type == SDL_QUIT) {
        quitRequested = true;
    }
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        quitRequested = true;
    }
}

bool InputManager::isKeyPressed(SDL_Scancode key) const {
    return keyboardState && keyboardState[key];
}

bool InputManager::shouldQuit() const {
    return quitRequested;
}
