//
// Created by gebruiker on 18/11/2025.
//

#include "PacMan.h"
model::PacMan::PacMan(const Vec2D& startpos, float speed)
    : Entity(startpos), m_position(startpos), m_speed(speed), m_direction(Direction::Right),
      m_requestedDirection(Direction::None) {}
void model::PacMan::update(const double deltaTime, World& world) {
    // todo: implement movement and collision logic
}
Direction model::PacMan::getDirection() const { return m_direction; }
void model::PacMan::setDirection(Direction dir) {
    if (dir != m_direction) {
        m_direction = dir;
        events::Event event{events::EventType::DirectionChanged};
        notify(event);
    }
}
void model::PacMan::setRequestedDirection(Direction direction) { m_requestedDirection = direction; }