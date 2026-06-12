#pragma once
#include "Entity.hpp"

class Boulder : public Entity {
private:
    float fallTimer = 0.0f;
    bool falling = false;

public:
    Boulder(int x, int y);
    bool isFalling() const;
    void update(float deltaTime, TileMap& map) override;
};
