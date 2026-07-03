#include "Enemy.hpp"

Enemy::Enemy(int x, int y, SDL_Texture* texture) : Entity(x, y, SDL_Color{220, 60, 80, 255}, texture) {}

void Enemy::aktualisieren(float deltaTime, TileMap& map) {
    moveTimer += deltaTime;
    if (moveTimer < 0.22f) return;
    moveTimer = 0.0f;

    int dx = direction == Direction::Left ? -1 : 1;
    int newX = position.x + dx;
    int newY = position.y;

    if (map.istBegehbar(newX, newY)) {
        position.x = newX;
    } else {
        direction = direction == Direction::Left ? Direction::Right : Direction::Left;
    }
}
