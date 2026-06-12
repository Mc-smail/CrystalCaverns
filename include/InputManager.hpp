#pragma once
#include <SDL.h>

class InputManager {
private:
    const Uint8* keyboardState = nullptr;
    bool quitRequested = false;

public:
    void update();
    void handleEvent(const SDL_Event& event);
    bool isKeyPressed(SDL_Scancode key) const;
    bool shouldQuit() const;
};
