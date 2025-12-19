/**
 *@file Wall.h
 *@brief Declaration of the Wall class representing wall entities in the game.
 */

#ifndef PACMAN_WALL_H
#define PACMAN_WALL_H
#include "Entity.h"

namespace model {
/** @brief Wall entity representing immovable obstacles in the game world.*/
class Wall : public Entity {
public:
    /** Wall constructor*/
    explicit Wall(const Vec2D& pos) : Entity(pos) {}
    void update(const double, World&) override {
        // walls do not have any update logic  because they dont move
        // keep it for posibility to add moving walls
    }
};
} // namespace model
#endif // PACMAN_WALL_H
