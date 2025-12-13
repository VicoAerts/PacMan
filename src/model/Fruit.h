/**
 * @file Fruit.h
 * @brief Definition of the fruit class representing a collectible item in the game.
 */

#ifndef PACMAN_FRUIT_H
#define PACMAN_FRUIT_H
#include "Collectable.h"
namespace model {
class Fruit : public Collectable {
public:
    /** Fruit constructor */
    explicit Fruit(const Vec2D& pos) : Collectable(pos) {}
    /** Get the type of collectable */
    [[nodiscard]] CellType getCollectableType() const override { return FRUIT; }
    /** collect method override to notify fruit eaten event */
    void collect() override {
        m_collected = true;
        events::Event event{events::EventType::FruitEaten};
        notify(event, *this);
    }
    /** on collide with pacman override to notify fruit eaten event */
    events::Event onCollideWithPacMan() override {
        if (!m_collected) {
            collect();
            return {events::EventType::FruitEaten};
        }
        return {events::EventType::None};
    }
};
} // namespace model

#endif // PACMAN_FRUIT_H
