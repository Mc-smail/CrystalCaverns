#pragma once
#include "Entity.hpp"

class Enemy : public Entity {
private:
    Direction direction = Direction::Left;
    float moveTimer = 0.0f;

public:
    Enemy(int x, int y);
    void update(float deltaTime, TileMap& map) override;
};
