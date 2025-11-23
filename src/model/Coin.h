/**
 * @file Coin.h
 * @brief Definition of the Coin class representing a collectible item in the game.
 */

#ifndef PACMAN_COIN_H
#define PACMAN_COIN_H
#include "Entity.h"

namespace model {
class Coin : public Entity {
public:
    /** Coin constructor */
    explicit Coin(const Vec2D& pos) : Entity(pos) {}

    void update(const double, World&) override {
        // Coins do not have any update logic as they are static collectibles.
    }
};
} // namespace model

#endif // PACMAN_COIN_H
