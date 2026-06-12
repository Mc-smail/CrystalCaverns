#pragma once
#include "Entity.hpp"
#include "InputManager.hpp"

class Player : public Entity {
private:
    int crystals = 0;
    float moveCooldown = 0.0f;

public:
    Player(int x, int y);
    void handleInput(const InputManager& input, TileMap& map);
    void move(Direction direction, TileMap& map);
    void collect(TileMap& map);
    int getCrystals() const;
    void update(float deltaTime, TileMap& map) override;
};
