#pragma once
#include <SDL.h>

class InputManager {
private:
    const Uint8* keyboardState = nullptr;
    bool quitRequested = false;

public:
    void aktualisiereTastatur();
    void verarbeiteEvent(const SDL_Event& event);
    bool tasteGedrueckt(SDL_Scancode key) const;
    bool sollBeenden() const;
};
