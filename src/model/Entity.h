/**
 *@file Entity.h
 *@brief Base class for all entities in the game model.
 */

#ifndef PACMAN_ENITYMODEL_H
#define PACMAN_ENITYMODEL_H
#include "../events/Event.h"
#include "../util/Vec2D.h"
#include "Subject.h"
namespace model {
/** Forward declaration of World class */
class World;

/** 2D Vector structure */

class Entity : public Subject {

protected:
    /** Constructor to initialize entity on position */
    explicit Entity(const Vec2D& pos) : m_position(pos) {}

    /** Position of the entity itself so member position in 2D space  */
    Vec2D m_position;

public:
    /**update entity*/
    virtual void update(const double deltaTime, World& world) = 0;

    /** Entity destructor */
    virtual ~Entity() = default;

    /** get position of entity */
    [[nodiscard]] Vec2D getPosition() const { return m_position; }

    /** set position of entity */
    void setPosition(const Vec2D& pos) {
        m_position = pos;
        events::Event event{events::EventType::PositionChanged};
        notify(event, *this);
    }
    /** virtual function to help input handling*/
    virtual void handleInput(Direction dir) {};

    /** virtual function to get direction*/
    virtual Direction getDirection() const { return Direction::None; };

    /** virtual function for collisions*/
    virtual events::Event onCollideWithPacMan() { return {events::EventType::None}; };
    /** virtual reset function to place entity back to start pos*/
    virtual void reset() {};
};
} // namespace model
#endif // PACMAN_ENITYMODEL_H
