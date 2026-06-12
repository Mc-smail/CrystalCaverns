#pragma once
#include "Entity.hpp"

class Enemy : public Entity {
private:
    Direction direction = Direction::Left;
    float moveTimer = 0.0f;

public:
    Enemy(int x, int y, SDL_Texture* texture = nullptr);
    void update(float deltaTime, TileMap& map) override;
};
