//
// Created by gebruiker on 22/11/2025.
//

#include "TextureManager.h"

sf::Texture util::TextureManager::textureSheet;
constexpr int util::TextureManager::TileSize;
void util::TextureManager::init(const std::string& id, const std::string& filename) {
    if (!textureSheet.loadFromFile("../assets/" + filename)) {
        throw std::runtime_error("Could not load texture sheet: " + filename);
    }
}
sf::Sprite util::TextureManager::getSprite(spriteType type, Direction dir) {
    // coordinates on the sprite sheet
    int col = 0;
    int row = 0;
    // basis no direction
    switch (type) {
    case spriteType::PACMAN:
        col = 17;
        row = 0;
        break;
    case spriteType::RED_GHOST:
        col = 13;
        row = 0;
        break;
    case spriteType::COIN:
        col = 8;
        row = 8;
        break;
    }
    // adjust row based on direction for pacman
    if (type == spriteType::PACMAN) {
        switch (dir) {
        case Direction::Right:
            row = 0;
            break;
        case Direction::Down:
            row = 4;
            break;
        case Direction::Left:
            row = 7;
            break;
        case Direction::Up:
            row = 10;
            break;
        case Direction::None:
            break;
        }
    }
    // adjust row based on direction for ghost
    if (type == spriteType::RED_GHOST /* of alle andere ghots want op zelfde rij zelfde kant*/) {
        switch (dir) {
        case Direction::Right:
            row = 1;
            break;
        case Direction::Down:
            row = 3;
            break;
        case Direction::Left:
            row = 5;
            break;
        case Direction::Up:
            row = 7;
            break;
        case Direction::None:
            break;
        }
    }

    sf::IntRect rect(col * TileSize, row * TileSize, TileSize, TileSize);
    sf::Sprite sprite;
    sprite.setTexture(textureSheet);
    sprite.setTextureRect(rect);
    // center
    sprite.setOrigin(TileSize / 2.0f, TileSize / 2.0f);
    return sprite;
}