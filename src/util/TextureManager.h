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
/** Enumeration for different sprite types */
enum class spriteType { PACMAN, GHOST, COIN, FRUIT, WALL };

namespace util {
/** TextureManager class for loading and managing game textures */
class TextureManager {
public:
    /** Load all textures from sprite sheet */
    static void init(const std::string& id, const std::string& filename);

    /** get textures ghost id and direction are default for textures who dont need these features*/
    static sf::Sprite getSprite(spriteType type, Direction dir = Direction::None, int ghostId = 0);

    /** get animation frames for pacMan*/
    static std::vector<sf::IntRect> getPacManFrames(Direction dir = Direction::None);
    /** get Ghost animation frames  */
    static std::vector<sf::IntRect> getGhostFrames(Direction dir = Direction::None, int ghostId = 1,
                                                   int mode = 2); // 2 is chase mode
    /** load the score font */
    static void loadScoreFont();

    /** get the score font */
    static const sf::Font& getScoreFont();

private:
    static sf::Texture textureSheet;
    static sf::Font scoreFont;
    static constexpr int TileSize = 50;
};

} // namespace util

#endif // PACMAN_TEXTUREMANAGER_H
