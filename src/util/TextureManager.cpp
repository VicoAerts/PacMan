//
// Created by gebruiker on 22/11/2025.
//

#include "TextureManager.h"

#include "../model/Ghost.h"

sf::Texture util::TextureManager::textureSheet;
constexpr int util::TextureManager::TileSize;
sf::Font util::TextureManager::scoreFont;
void util::TextureManager::init(const std::string& id, const std::string& filename) {
    if (!textureSheet.loadFromFile("../assets/" + filename)) {
        throw std::runtime_error("Could not load texture sheet: " + filename);
    }
}
sf::IntRect cropRect(int col, int row, int TileSize) {
    // cropping parameters
    int left = 3;
    int top = 5;
    int right = 14;
    int bottom = 12;

    int width = TileSize - left - right;
    int height = TileSize - top - bottom;
    sf::IntRect rect(col * TileSize + left, row * TileSize + top, width, height);

    return rect;
}
sf::Sprite util::TextureManager::getSprite(spriteType type, Direction dir, int ghostId) {
    // coordinates on the sprite sheet
    int col = 0;
    int row = 0;
    sf::Sprite sprite;
    sprite.setTexture(textureSheet);
    // basis no direction
    switch (type) {
    case spriteType::PACMAN:
        col = 17;
        row = 0;
        break;
    case spriteType::GHOST:
        switch (ghostId) {
        case 1:
            col = 13;
            row = 0;
            break;
        case 2:
            col = 14;
            row = 0;
            break;
        case 3:
            col = 15;
            row = 0;
            break;
        case 4:
            col = 16;
            row = 0;
            break;
        default:
            col = 13;
            row = 0;
            break;
        }
        break;
    case spriteType::COIN:
        col = 8;
        row = 8;
        break;
    case spriteType::FRUIT:
        col = 12;
        row = 0;
        break;
    }
    // adjust row based on direction for pacman
    if (type == spriteType::PACMAN) {
        switch (dir) {
        case Direction::Right:
            row = 1;
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
            row = 0;
            break;
        }
    }
    // adjust row based on direction for ghost
    if (type == spriteType::GHOST) {
        switch (dir) {
        case Direction::Right:
            row = 0;
            break;
        case Direction::Down:
            row = 2;
            break;
        case Direction::Left:
            row = 4;
            break;
        case Direction::Up:
            row = 6;
            break;
        case Direction::None:
            row = 0;
            break;
        }
    }

    // cropping parameters
    int left = 3;
    int top = 5;
    int right = 14;
    int bottom = 12;

    int width = TileSize - left - right;
    int height = TileSize - top - bottom;
    sf::IntRect rect(col * TileSize + left, row * TileSize + top, width, height);
    // set texture rect and origin
    sprite.setTextureRect(rect);
    sprite.setOrigin(width / 2.f, height / 2.f);
    return sprite;
}
std::vector<sf::IntRect> util::TextureManager::getPacManFrames(Direction dir) {
    int col = 17;

    int baseRow = 1;
    switch (dir) {
    case Direction::Right:
        baseRow = 1;
        break;
    case Direction::Down:
        baseRow = 4;
        break;
    case Direction::Left:
        baseRow = 7;
        break;
    case Direction::Up:
        baseRow = 10;
        break;
    case Direction::None:
        baseRow = 1;
        break;
    }

    int left = 3, top = 5, right = 14, bottom = 12;
    std::vector<sf::IntRect> frames;
    frames.reserve(4);

    // 3 rows of animation frames
    // 4 to make smooth loop close , half open , fully open , half open and again
    for (int i = 0; i < 3; ++i) {
        int row = baseRow + (i - 1);
        int width = TileSize - left - right;
        int height = TileSize - top - bottom;
        sf::IntRect rect(col * TileSize + left, row * TileSize + top, width, height);
        frames.push_back(rect);
    }
    // add the half open frame again to loop smoothly
    int row = baseRow + 1;
    int width = TileSize - left - right;
    int height = TileSize - top - bottom;
    sf::IntRect rect(col * TileSize + left, row * TileSize + top, width, height);
    frames.push_back(rect);

    return frames;
}
std::vector<sf::IntRect> util::TextureManager::getGhostFrames(Direction dir, int ghostId, int mode) {

    int col;
    switch (ghostId) {
    case 1:
        col = 0;
        break;
    case 2:
        col = 1;
        break;
    case 3:
        col = 2;
        break;
    case 4:
        col = 3;
        break;
    default:
        // green ghost to know if something went wrong
        col = 5;
        break;
    }
    int baseRow = 0;
    switch (dir) {
    case Direction::Right:
        baseRow = 0;
        break; // rows 0 & 1
    case Direction::Down:
        baseRow = 2;
        break; // rows 2 & 3
    case Direction::Left:
        baseRow = 4;
        break; // rows 4 & 5
    case Direction::Up:
        baseRow = 6;
        break; // rows 6 & 7
    case Direction::None:
        baseRow = 0;
        break;
    }
    if (mode == 3) {
        col = 0;      // blue ghost for fear mode
        baseRow = 11; // rows 11 & 12
    }
    int left = 3;
    int top = 5;
    int right = 14;
    int bottom = 12;

    int width = TileSize - left - right;
    int height = TileSize - top - bottom;

    std::vector<sf::IntRect> frames;
    frames.reserve(2);

    // 2 rows of animation frames baserow and baserow +1
    for (int i = 0; i < 2; ++i) {
        int row = baseRow + i;
        sf::IntRect rect(col * TileSize + left, row * TileSize + top, width, height);
        frames.push_back(rect);
    }

    return frames;
}

void util::TextureManager::loadScoreFont() {

    if (!scoreFont.loadFromFile("../assets/emulogic-font/Emulogic-zrEw.ttf")) {
        throw std::runtime_error("Could not load score font");
    }
}
const sf::Font& util::TextureManager::getScoreFont() { return scoreFont; }
