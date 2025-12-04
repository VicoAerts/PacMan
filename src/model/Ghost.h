/**
 *@file Ghost.h
 *@brief Declaration of the Ghost class representing the Ghost entity in the game.
 * ghost uses 4 modes: wait, chase, fear, eaten
 */

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "../util/Direction.h"
#include "Entity.h"
#include "World.h"

enum class GhostMode { Wait, Chase, Fear, Eaten };
enum class GhostType { Random, FacingPacman, DirectChase };

namespace model {
class Ghost : public Entity {
public:
    /** current mode of the ghost */
    explicit Ghost(const Vec2D& startpos, float speed, int ghostId);
    /** update ghost position and state*/
    void update(const double deltaTime, World& world) override;
    /** get current mode of the ghost*/
    [[nodiscard]] GhostMode getMode() const;
    /** set current mode of the ghost*/
    void setMode(GhostMode mode);
    /** get ghost type*/
    [[nodiscard]] GhostType getType() const;
    /** get ghost id*/
    [[nodiscard]] int getId() const;
    /** get valid directions for the ghost to move in*/
    std::vector<Direction> getValidDirections(const World& world) const;

    /**Choose a new direction for the ghost at random*/
    Direction chooseRandomDirection(const std::vector<Direction>& validDirections);

    /**Choose a new direction for the ghost to face Pacman */
    void chooseFacingPacmanDirection(const World& world, const Vec2D& pacmanPos);

private:
    GhostMode m_mode;
    GhostType m_type;
    float m_speed;
    Direction m_direction;
    Vec2D m_startpos;
    int m_id;
};
} // namespace model
  // namespace model
#endif // PACMAN_GHOST_H
