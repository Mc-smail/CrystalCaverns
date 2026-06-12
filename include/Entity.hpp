#pragma once
#include <SDL.h>
#include "Types.hpp"
#include "TileMap.hpp"

class Entity {
protected:
    Vector2i position;
    SDL_Color renderColor{255,255,255,255};
    SDL_Texture* texture = nullptr;
    bool alive = true;

public:
    Entity(int x, int y, SDL_Color color, SDL_Texture* texture = nullptr);
    virtual ~Entity() = default;

    virtual void update(float deltaTime, TileMap& map) = 0;
    virtual void render(SDL_Renderer* renderer, int tileSize) const;

    Vector2i getPosition() const;
    SDL_Rect getHitbox(int tileSize) const;
    bool isAlive() const;
    void kill();
};
