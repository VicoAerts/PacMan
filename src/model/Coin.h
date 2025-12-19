/**
 * @file Coin.h
 * @brief Definition of the Coin class representing a collectible coin item in the game.
 */

#ifndef PACMAN_COIN_H
#define PACMAN_COIN_H
#include "Collectable.h"

namespace model {
/** @brief collectable coin entity that increases score when collected */
class Coin : public Collectable {
public:
    /** Coin constructor */
    explicit Coin(const Vec2D& pos) : Collectable(pos){};

    /** Get the type of collectable */
    [[nodiscard]] CellType getCollectableType() const override { return COIN; }

    /** collect method override to notify coin eaten event */
    void collect() override {
        m_collected = true;
        events::Event event{events::EventType::CoinEaten};
        notify(event, *this);
    }
    /** on collide with pacman override to notify coin eaten event */
    events::Event onCollideWithPacMan() override {
        if (!m_collected) {
            collect();
            return {events::EventType::CoinEaten};
        }
        return {events::EventType::None};
    }
};
} // namespace model

#endif // PACMAN_COIN_H
