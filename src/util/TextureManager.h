/**
 *@file TextureManager.h
 *loads the textures and crops them out of the sprite sheet.
 */

#ifndef PACMAN_TEXTUREMANAGER_H
#define PACMAN_TEXTUREMANAGER_H
#include "../util/Direction.h"
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>

enum class Direction;
enum class spriteType { PACMAN, RED_GHOST, COIN, FRUIT, WALL };

namespace util {
class TextureManager {
public:
    /** Load all textures from sprite sheet */
    static void init(const std::string& id, const std::string& filename);

    /** get textures */
    static sf::Sprite getSprite(spriteType type, Direction dir = Direction::None);

private:
    static sf::Texture textureSheet;
    static constexpr int TileSize = 50;
};

} // namespace util

#endif // PACMAN_TEXTUREMANAGER_H
