#include "Figur.hpp"

Figur::Figur(int x, int y, SDL_Color color, SDL_Texture* texture)
    : position{x, y}, renderColor(color), texture(texture) {}

void Figur::zeichnen(SDL_Renderer* renderer, int tileSize) const {
    SDL_Rect rect{position.x * tileSize + 2, position.y * tileSize + 2, tileSize - 4, tileSize - 4};
    if (texture) {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
        return;
    }
    SDL_SetRenderDrawColor(renderer, renderColor.r, renderColor.g, renderColor.b, renderColor.a);
    SDL_RenderFillRect(renderer, &rect);
}

Position2D Figur::getPosition() const { return position; }

SDL_Rect Figur::getHitbox(int tileSize) const {
    return {position.x * tileSize, position.y * tileSize, tileSize, tileSize};
}

bool Figur::isAlive() const { return alive; }
void Figur::kill() { alive = false; }
