//
// Created by gebruiker on 22/11/2025.
//

#ifndef PACMAN_VEC2D_H
#define PACMAN_VEC2D_H
#include "Direction.h"

struct Vec2D {
    float x{0.f};
    float y{0.f};
};

// Convert Direction to Vec2D
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
