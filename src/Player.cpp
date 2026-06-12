#include "Player.hpp"

Player::Player(int x, int y) : Entity(x, y, SDL_Color{255, 220, 70, 255}) {}

void Player::handleInput(const InputManager& input, TileMap& map) {
    if (moveCooldown > 0.0f) return;

    if (input.isKeyPressed(SDL_SCANCODE_UP) || input.isKeyPressed(SDL_SCANCODE_W)) {
        move(Direction::Up, map);
    } else if (input.isKeyPressed(SDL_SCANCODE_DOWN) || input.isKeyPressed(SDL_SCANCODE_S)) {
        move(Direction::Down, map);
    } else if (input.isKeyPressed(SDL_SCANCODE_LEFT) || input.isKeyPressed(SDL_SCANCODE_A)) {
        move(Direction::Left, map);
    } else if (input.isKeyPressed(SDL_SCANCODE_RIGHT) || input.isKeyPressed(SDL_SCANCODE_D)) {
        move(Direction::Right, map);
    }
}

void Player::move(Direction direction, TileMap& map) {
    int newX = position.x;
    int newY = position.y;

    switch (direction) {
        case Direction::Up:    --newY; break;
        case Direction::Down:  ++newY; break;
        case Direction::Left:  --newX; break;
        case Direction::Right: ++newX; break;
        case Direction::None: return;
    }

    if (map.isWalkable(newX, newY)) {
        position.x = newX;
        position.y = newY;
        collect(map);
        moveCooldown = 0.12f;
    }
}

void Player::collect(TileMap& map) {
    Tile& tile = map.getTile(position.x, position.y);
    if (tile.isCollectible()) {
        ++crystals;
        tile.setType(TileType::Empty);
    }
    if (tile.getType() == TileType::Dirt) {
        tile.setType(TileType::Empty);
    }
}

int Player::getCrystals() const { return crystals; }

void Player::update(float deltaTime, TileMap&) {
    if (moveCooldown > 0.0f) {
        moveCooldown -= deltaTime;
    }
}
