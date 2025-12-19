/**
 * @file Collectable.h
 * @brief Declaration of the Collectable class representing items that can be collected in the game.
 * Collectables are static entities that can be collected by Pac-Man
 * and trigger score-related events.
 */
#ifndef PACMAN_COLLECTABLE_H
#define PACMAN_COLLECTABLE_H
#include "Entity.h"
#include "GridMap.h"

namespace model {
/** Abstract class for collectable items in the game */
class Collectable : public Entity {
protected:
    bool m_collected;

public:
    /** Collectable constructor */
    explicit Collectable(const Vec2D& pos) : Entity(pos), m_collected(false) {}
    /** Check if the collectable has been collected */
    [[nodiscard]] bool isCollected() const { return m_collected; }
    /** Set the collectable as collected */
    virtual void collect() = 0;
    /** Update method for collectable (no-op) */
    void update(const double, World&) override {
        // Coins do not have any update logic as they are static collectibles.
    }
    /** pure virtual on collide with pacman method */
    events::Event onCollideWithPacMan() override = 0;
    /** virtual collectable type getter */
    [[nodiscard]] virtual CellType getCollectableType() const = 0;
};
} // namespace model

#endif // PACMAN_COLLECTABLE_H
