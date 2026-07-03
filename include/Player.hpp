#pragma once
#include "Entity.hpp"
#include "InputManager.hpp"

class Player : public Entity {
private:
    int crystals = 0;
    float moveCooldown = 0.0f;

public:
    Player(int x, int y, SDL_Texture* texture = nullptr);
    void verarbeiteEingabe(const InputManager& input, TileMap& map);
    void bewege(Direction direction, TileMap& map);
    void sammleFeld(TileMap& map);
    int getKristalle() const;
    void aktualisieren(float deltaTime, TileMap& map) override;
};
