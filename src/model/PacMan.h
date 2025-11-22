/**
 *@file PacMan.h
 *@brief Declaration of the PacMan class representing the PacMan entity in the game.
 */
#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "Entity.h"

#include <SFML/Graphics/Glsl.hpp>

namespace model {
enum class Direction { Left, Right, Up, Down };
class PacMan : public Entity {
public:
    /** pacman constructor*/
    explicit PacMan(const Vec2D& pos) : Entity(pos), m_direction(Direction::Right) {}
    /** update pacman position and state*/
    void update(const double deltaTime, World& world) override;
    /** get current direction of pacman*/
    [[nodiscard]] Direction getDirection() const;
    /** set current direction of pacman*/
    void setDirection(Direction dir);

private:
    Direction m_direction;
};
} // namespace model
#endif // PACMAN_PACMAN_H
