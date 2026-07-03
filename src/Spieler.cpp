#include "Spieler.hpp"

Spieler::Spieler(int x, int y, SDL_Texture* texture) : Figur(x, y, SDL_Color{255, 220, 70, 255}, texture) {}

void Spieler::verarbeiteEingabe(const Tastatur& input, LevelKarte& map) {
    if (moveCooldown > 0.0f) return;

    if (input.tasteGedrueckt(SDL_SCANCODE_UP) || input.tasteGedrueckt(SDL_SCANCODE_W)) {
        bewege(Richtung::Up, map);
    } else if (input.tasteGedrueckt(SDL_SCANCODE_DOWN) || input.tasteGedrueckt(SDL_SCANCODE_S)) {
        bewege(Richtung::Down, map);
    } else if (input.tasteGedrueckt(SDL_SCANCODE_LEFT) || input.tasteGedrueckt(SDL_SCANCODE_A)) {
        bewege(Richtung::Left, map);
    } else if (input.tasteGedrueckt(SDL_SCANCODE_RIGHT) || input.tasteGedrueckt(SDL_SCANCODE_D)) {
        bewege(Richtung::Right, map);
    }
}

void Spieler::bewege(Richtung direction, LevelKarte& map) {
    int newX = position.x;
    int newY = position.y;

    switch (direction) {
        case Richtung::Up:    --newY; break;
        case Richtung::Down:  ++newY; break;
        case Richtung::Left:  --newX; break;
        case Richtung::Right: ++newX; break;
        case Richtung::None: return;
    }

    if (map.istBegehbar(newX, newY)) {
        position.x = newX;
        position.y = newY;
        sammleFeld(map);
        moveCooldown = 0.12f;
    }
}

void Spieler::sammleFeld(LevelKarte& map) {
    Feld& tile = map.getFeld(position.x, position.y);
    if (tile.istSammelbar()) {
        ++crystals;
        tile.setTyp(FeldTyp::Empty);
    }
    if (tile.getTyp() == FeldTyp::Dirt) {
        tile.setTyp(FeldTyp::Empty);
    }
}

int Spieler::getKristalle() const { return crystals; }

void Spieler::aktualisieren(float deltaTime, LevelKarte&) {
    if (moveCooldown > 0.0f) {
        moveCooldown -= deltaTime;
    }
}
