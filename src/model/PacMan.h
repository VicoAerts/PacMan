/**
 *@file PacMan.h
 *@brief Declaration of the PacMan class representing the PacMan entity in the game.
 *
 */
#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "../util/Direction.h"
#include "../util/Vec2D.h"
#include "Entity.h"

namespace model {
/**
 * @brief Pac-Man entity controlled by the player.
 *
 * Contains movement logic and collision handling.
 * Part of the game logic layer (no rendering code).
 */
class PacMan : public Entity {
public:
    /** pacman constructor*/
    explicit PacMan(const Vec2D& startpos, float speed);
    /** update pacman position and state*/
    void update(const double deltaTime, World& world) override;
    /** get current direction of pacman*/
    [[nodiscard]] Direction getDirection() const override;
    /** set current direction of pacman*/
    void setDirection(Direction dir);
    /** set requested direction of pacman*/
    void setRequestedDirection(Direction direction);
    /** hanlde input for pacman*/
    void handleInput(Direction dir) override;
    /** reset pacman to start position*/
    void reset(int currentLevel) override;

private:
    Direction m_direction;
    Vec2D m_startpos;
    float m_speed;
    Direction m_requestedDirection;
};
} // namespace model
#endif // PACMAN_PACMAN_H
