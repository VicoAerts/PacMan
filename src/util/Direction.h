/**
 * @file Direction.h
 * @brief Defines movement directions and related helper functions.
 */
#ifndef PACMAN_DIRECTION_H
#define PACMAN_DIRECTION_H
/** Enumeration for movement directions */
enum class Direction { Left, Right, Up, Down, None };

/**
 * @brief Returns the opposite of a given direction.
 *
 * @param d Direction for which the opposite is requested
 * @return Opposite direction, or Direction::None if undefined
 */
inline Direction opposite(Direction d) {
    switch (d) {
    case Direction::Up:
        return Direction::Down;
    case Direction::Down:
        return Direction::Up;
    case Direction::Left:
        return Direction::Right;
    case Direction::Right:
        return Direction::Left;
    default:
        return Direction::None;
    }
}

#endif // PACMAN_DIRECTION_H
