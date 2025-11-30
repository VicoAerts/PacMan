//
// Created by gebruiker on 18/11/2025.
//

#include "PacMan.h"

#include "World.h"

#include <iostream>
model::PacMan::PacMan(const Vec2D& startpos, float speed)
    : Entity(startpos), m_speed(speed), m_direction(Direction::None), m_requestedDirection(Direction::None) {
    notify(events::Event{events::EventType::PositionChanged}, *this);
    notify(events::Event{events::EventType::DirectionChanged}, *this);
}

void model::PacMan::update(const double deltaTime, World& world) {
    // try to change to the requested direction if possible
    Vec2D currentPos = m_position;
    Vec2D wantedMove;
    if (m_requestedDirection != Direction::None && m_requestedDirection != m_direction) {
        wantedMove = Vec2D{dirToVector(m_requestedDirection).x * static_cast<float>(m_speed * deltaTime),
                           dirToVector(m_requestedDirection).y * static_cast<float>(m_speed * deltaTime)};

        // first pull position to center to smooth turns
        Vec2D testPos = currentPos;
        world.snapToCorridor(testPos, m_requestedDirection);
        if (world.isMoveValid(testPos, wantedMove, *this)) {
            currentPos = testPos;
            world.snapToCorridor(currentPos, m_requestedDirection);
            setPosition(currentPos);
            setDirection(m_requestedDirection);
        }
    }
    if (m_direction == Direction::None) {
        return;
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
        currentPos.x += move.x;
        currentPos.y += move.y;
        world.snapToCorridor(currentPos, m_direction);
        setPosition(currentPos);

    } else {
        // we hit a wall, stop moving
        m_direction = Direction::None;
    }
    world.handlePacManCollisions(currentPos);
}
Direction model::PacMan::getDirection() const { return m_direction; }
void model::PacMan::setDirection(Direction dir) {
    if (dir != m_direction) {
        m_direction = dir;
        notify(events::Event{events::EventType::DirectionChanged, getDirection()}, *this);
    }
}
void model::PacMan::setRequestedDirection(Direction direction) { m_requestedDirection = direction; }
void model::PacMan::handleInput(Direction dir) { setRequestedDirection(dir); }