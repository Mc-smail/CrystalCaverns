#pragma once
#include "Entity.hpp"

class Boulder : public Entity {
private:
    float fallTimer = 0.0f;
    bool falling = false;

public:
    Boulder(int x, int y, SDL_Texture* texture = nullptr);
    bool faelltGerade() const;
    void aktualisieren(float deltaTime, TileMap& map) override;
};
