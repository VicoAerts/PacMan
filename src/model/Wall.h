/**
 *@file Wall.h
 *@brief Declaration of the Wall class representing wall entities in the game.
 */

#ifndef PACMAN_WALL_H
#define PACMAN_WALL_H
#include "Entity.h"

namespace model {
class Wall : public Entity {
public:
    /** Wall constructor*/
    explicit Wall(const Vec2D& pos) : Entity(pos) {}
};
} // namespace model
#endif // PACMAN_WALL_H
