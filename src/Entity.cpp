#include "Entity.hpp"

Entity::Entity(int x, int y, SDL_Color color) : position{x, y}, renderColor(color) {}

void Entity::render(SDL_Renderer* renderer, int tileSize) const {
    SDL_Rect rect{position.x * tileSize + 4, position.y * tileSize + 4, tileSize - 8, tileSize - 8};
    SDL_SetRenderDrawColor(renderer, renderColor.r, renderColor.g, renderColor.b, renderColor.a);
    SDL_RenderFillRect(renderer, &rect);
}

Vector2i Entity::getPosition() const { return position; }

SDL_Rect Entity::getHitbox(int tileSize) const {
    return {position.x * tileSize, position.y * tileSize, tileSize, tileSize};
}

bool Entity::isAlive() const { return alive; }
void Entity::kill() { alive = false; }
