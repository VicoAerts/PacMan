/**
 * @file Vec2D.h
 * @brief Defines a simple 2D vector structure and direction conversion utility.
 */

#ifndef PACMAN_VEC2D_H
#define PACMAN_VEC2D_H
#include "Direction.h"

/**
 * @brief Simple 2D vector used for positions and directions.
 */
struct Vec2D {
    float x{0.f};
    float y{0.f};
};

/**
 * @brief Converts a Direction enum value to a 2D direction vector.
 *
 * @param d Direction to convert
 * @return Corresponding unit vector, or (0,0) if Direction::None
 */
static Vec2D dirToVector(Direction d) {
    switch (d) {
    case Direction::Left:
        return {-1.f, 0.f};
    case Direction::Right:
        return {1.f, 0.f};
    case Direction::Up:
        return {0.f, 1.f};
    case Direction::Down:
        return {0.f, -1.f};
    default:
        return {0.f, 0.f};
    }
}

#endif // PACMAN_VEC2D_H
