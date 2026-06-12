#include "Boulder.hpp"

Boulder::Boulder(int x, int y) : Entity(x, y, SDL_Color{150, 150, 150, 255}) {}

bool Boulder::isFalling() const { return falling; }

void Boulder::update(float deltaTime, TileMap& map) {
    fallTimer += deltaTime;
    if (fallTimer < 0.22f) return;
    fallTimer = 0.0f;

    int belowX = position.x;
    int belowY = position.y + 1;

    if (map.isWalkable(belowX, belowY)) {
        position.y = belowY;
        falling = true;
    } else {
        falling = false;
    }
}
