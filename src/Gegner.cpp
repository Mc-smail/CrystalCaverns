#include "Gegner.hpp"

Gegner::Gegner(int x, int y, SDL_Texture* texture) : Figur(x, y, SDL_Color{220, 60, 80, 255}, texture) {}

void Gegner::aktualisieren(float deltaTime, LevelKarte& map) {
    moveTimer += deltaTime;
    if (moveTimer < 0.22f) return;
    moveTimer = 0.0f;

    int dx = direction == Richtung::Left ? -1 : 1;
    int newX = position.x + dx;
    int newY = position.y;

    if (map.istBegehbar(newX, newY)) {
        position.x = newX;
    } else {
        direction = direction == Richtung::Left ? Richtung::Right : Richtung::Left;
    }
}
