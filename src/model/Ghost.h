/**
 *@file Ghost.h
 *@brief Declaration of the Ghost class representing the Ghost entity in the game.
 * ghost uses 4 modes: wait, chase, fear, eaten
 */

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "Entity.h"

enum class GhostMode { Wait, Chase, Fear, Eaten };

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

private:
    GhostMode m_mode;
    float m_speed;
    Direction m_direction;
    Vec2D m_startpos;
    int m_id;
};
} // namespace model
  // namespace model
#endif // PACMAN_GHOST_H
