//
// Created by gebruiker on 18/11/2025.
//

#include "Ghost.h"
model::Ghost::Ghost(const Vec2D& startpos, float speed, int ghostId)
    : Entity(startpos), m_speed(speed), m_direction(Direction::None), m_mode(GhostMode::Chase), m_startpos(startpos),
      m_id(ghostId) {}

void model::Ghost::update(const double deltaTime, World& world) {}
GhostMode model::Ghost::getMode() const {}
void model::Ghost::setMode(GhostMode mode) {}