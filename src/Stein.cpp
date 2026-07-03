#include "Stein.hpp"

Stein::Stein(int x, int y, SDL_Texture* texture) : Figur(x, y, SDL_Color{150, 150, 150, 255}, texture) {}

bool Stein::faelltGerade() const { return falling; }

void Stein::aktualisieren(float deltaTime, LevelKarte& map) {
    fallTimer += deltaTime;
    if (fallTimer < 0.14f) return;
    fallTimer = 0.0f;

    int belowX = position.x;
    int belowY = position.y + 1;

    if (map.istBegehbar(belowX, belowY)) {
        position.y = belowY;
        falling = true;
    } else {
        falling = false;
    }
}
