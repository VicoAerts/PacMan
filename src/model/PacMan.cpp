//
// Created by gebruiker on 18/11/2025.
//

#include "PacMan.h"

#include "World.h"

#include <iostream>
model::PacMan::PacMan(const Vec2D& startpos, float speed)
    : Entity(startpos), m_speed(speed), m_direction(Direction::None), m_requestedDirection(Direction::None) {
    std::cout << "PacMan MODEL addr = " << this << '\n';
}

void model::PacMan::update(const double deltaTime, World& world) {
    // try to change to the requested direction if possible
    Vec2D wantedMove;
    if (m_requestedDirection != Direction::None && m_requestedDirection != m_direction) {
        wantedMove = Vec2D{dirToVector(m_requestedDirection).x * static_cast<float>(m_speed * deltaTime),
                           dirToVector(m_requestedDirection).y * static_cast<float>(m_speed * deltaTime)};
    }
    if (world.isMoveValid(m_position, wantedMove, *this)) {
        m_direction = m_requestedDirection;
    }

    Vec2D dirVec = dirToVector(m_direction);
    float scale = m_speed * deltaTime;

    Vec2D move;
    move.x = dirVec.x * scale;
    move.y = dirVec.y * scale;

    if (move.x == 0.f && move.y == 0.f) {
        return;
    }
    // check if move is valid
    if (world.isMoveValid(m_position, move, *this)) {
        m_position.x += move.x;
        m_position.y -= move.y;
    } else {
        // we hit a wall, stop moving
        m_direction = Direction::None;
        m_requestedDirection = Direction::None;
    }
    // std::cout << "Pacman position: (" << m_position.x << ", " << m_position.y << ")\n";
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