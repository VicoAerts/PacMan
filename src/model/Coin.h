/**
 * @file Coin.h
 * @brief Definition of the Coin class representing a collectible item in the game.
 */

#ifndef PACMAN_COIN_H
#define PACMAN_COIN_H
#include "Collectable.h"

namespace util {
class Coin : public Collectable {
public:
    /** Coin constructor */
    explicit Coin(const Vec2D& pos) : Collectable(pos) {}
};
} // namespace util

#endif // PACMAN_COIN_H
