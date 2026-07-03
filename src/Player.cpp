#include "Player.hpp"

Player::Player(int x, int y, SDL_Texture* texture) : Entity(x, y, SDL_Color{255, 220, 70, 255}, texture) {}

void Player::verarbeiteEingabe(const InputManager& input, TileMap& map) {
    if (moveCooldown > 0.0f) return;

    if (input.tasteGedrueckt(SDL_SCANCODE_UP) || input.tasteGedrueckt(SDL_SCANCODE_W)) {
        bewege(Direction::Up, map);
    } else if (input.tasteGedrueckt(SDL_SCANCODE_DOWN) || input.tasteGedrueckt(SDL_SCANCODE_S)) {
        bewege(Direction::Down, map);
    } else if (input.tasteGedrueckt(SDL_SCANCODE_LEFT) || input.tasteGedrueckt(SDL_SCANCODE_A)) {
        bewege(Direction::Left, map);
    } else if (input.tasteGedrueckt(SDL_SCANCODE_RIGHT) || input.tasteGedrueckt(SDL_SCANCODE_D)) {
        bewege(Direction::Right, map);
    }
}

void Player::bewege(Direction direction, TileMap& map) {
    int newX = position.x;
    int newY = position.y;

    switch (direction) {
        case Direction::Up:    --newY; break;
        case Direction::Down:  ++newY; break;
        case Direction::Left:  --newX; break;
        case Direction::Right: ++newX; break;
        case Direction::None: return;
    }

    if (map.istBegehbar(newX, newY)) {
        position.x = newX;
        position.y = newY;
        sammleFeld(map);
        moveCooldown = 0.12f;
    }
}

void Player::sammleFeld(TileMap& map) {
    Tile& tile = map.getFeld(position.x, position.y);
    if (tile.istSammelbar()) {
        ++crystals;
        tile.setTyp(TileType::Empty);
    }
    if (tile.getTyp() == TileType::Dirt) {
        tile.setTyp(TileType::Empty);
    }
}

int Player::getKristalle() const { return crystals; }

void Player::aktualisieren(float deltaTime, TileMap&) {
    if (moveCooldown > 0.0f) {
        moveCooldown -= deltaTime;
    }
}
