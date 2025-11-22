//
// Created by gebruiker on 18/11/2025.
//

#include "PacMan.h"
void model::PacMan::update(const double deltaTime, World& world) {
    // todo: implement movement and collision logic
}
model::Direction model::PacMan::getDirection() const { return m_direction; }
void model::PacMan::setDirection(Direction dir) {
    if (dir != m_direction) {
        m_direction = dir;
        events::Event event{events::EventType::DirectionChanged};
        notify(event);
    }
}