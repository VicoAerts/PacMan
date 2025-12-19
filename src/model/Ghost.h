/**
 * @file Ghost.h
 * @brief Declaration of the Ghost entity and its AI behavior.
 *
 * Ghosts have movement modes (Wait, Leaving, Chase) and can additionally
 * enter a temporary fear state when Pac-Man eats a fruit.
 */

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "../../config/config.h"
#include "../control/World.h"
#include "../events/Event.h"
#include "../util/Direction.h"
#include "Entity.h"

namespace model {
/** Enumeration for ghost movement modes */
enum class GhostMode { Wait, Leaving, Chase };
/**
 * Enumeration for ghost AI types
 * where facing pacman tries to cut pacman off
 * and direct chase goes straight towards pacman
 */
enum class GhostType { Random, FacingPacman, DirectChase };
/**
 * @brief Ghost entity with AI movement and fear behavior.
 *
 * Part of the game logic layer (no rendering code).
 */
class Ghost : public Entity {
public:
    /** current mode of the ghost */
    explicit Ghost(const Vec2D& startpos, float speed, int ghostId);
    /** update ghost position and state*/
    void update(const double deltaTime, World& world) override;
    /** get current mode of the ghost*/
    [[nodiscard]] GhostMode getMode() const;
    /**get current mode of the ghost as int*/
    [[nodiscard]] int getCurrentMode() const override;
    /** set current mode of the ghost*/
    void setMode(GhostMode mode);
    /** get ghost type*/
    [[nodiscard]] GhostType getType() const;
    /** get ghost id*/
    [[nodiscard]] int getId() const;
    /** get valid directions for the ghost to move in*/
    [[nodiscard]] std::vector<Direction> getValidDirections(const World& world) const;

    /**Choose a new direction for the ghost at random*/
    Direction chooseRandomDirection(World& world, double deltaTime) const;

    /**Choose a new direction for the ghost to face Pacman */
    Direction chooseFacingPacmanDirection(World& world, const Vec2D& pacmanPos, double deltaTime) const;
    /** set current direction of the ghost*/
    void setDirection(Direction dir);
    /** get current direction of the ghost*/
    [[nodiscard]] Direction getDirection() const override;
    /** get direction to target position*/
    Direction getDirectionToTarget(World& world, const Vec2D& targetPos, double deltaTime) const;
    /** choose direction away from target position*/
    Direction getDirectionAwayFromTarget(World& world, const Vec2D& targetPos, double deltaTime) const;
    /** handle colission with pacman*/
    events::Event onCollideWithPacMan() override;
    /** reset ghost to start position*/
    void reset() override;
    /** set ghost to scared mode*/
    void setScared(double duration, World& world) override;

private:
    GhostMode m_mode;
    GhostType m_type;
    float m_speed;
    Direction m_direction;
    Vec2D m_startpos;
    int m_id;
    bool m_waiting = true;
    double m_spawnDelay;
    double m_timeAlive = 0.0;
    Vec2D last_descision_Tile = {-1.f, -1.f};
    double m_fearTimeLeft = 0.0;
    bool m_isFeared = false;
};
} // namespace model
#endif // PACMAN_GHOST_H
