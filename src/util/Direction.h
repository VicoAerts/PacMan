//
// Created by gebruiker on 22/11/2025.
//

#ifndef PACMAN_DIRECTION_H
#define PACMAN_DIRECTION_H
enum class Direction { Left, Right, Up, Down, None };

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
