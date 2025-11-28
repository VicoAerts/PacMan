/**
 * @file Collectable.h
 * @brief Declaration of the Collectable class representing items that can be collected in the game.
 */
#ifndef PACMAN_COLLECTABLE_H
#define PACMAN_COLLECTABLE_H
#include "Entity.h"

namespace util {
class Collectable : public Entity {
private:
    bool m_collected;

public:
    /** Collectable constructor */
    explicit Collectable(const Vec2D& pos) : Entity(pos), m_collected(false) {}
    /** Check if the collectable has been collected */
    [[nodiscard]] bool isCollected() const { return m_collected; }
    /** Set the collectable as collected */
    void collect() {
        m_collected = true;
        events::Event event{events::EventType::CoinEaten};
        notify(event, *this);
    };
    /** Update method for collectable (no-op) */
    void update(const double, World&) override {
        // Coins do not have any update logic as they are static collectibles.
    }
    void onCollideWithPacMan() override {
        if (!m_collected) {
            collect();
        }
    }
};
} // namespace util

#endif // PACMAN_COLLECTABLE_H
