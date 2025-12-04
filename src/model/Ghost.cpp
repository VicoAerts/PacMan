//
// Created by gebruiker on 18/11/2025.
//

#include "Ghost.h"
model::Ghost::Ghost(const Vec2D& startpos, float speed, int ghostId)
    : Entity(startpos), m_speed(speed), m_direction(Direction::None), m_mode(GhostMode::Chase), m_startpos(startpos),
      m_id(ghostId) {
    switch (ghostId) {
    case 1:
        m_type = GhostType::Random;
        break;
    case 2:
        m_type = GhostType::FacingPacman;
        break;
    case 3:
        m_type = GhostType::FacingPacman;
        break;
    case 4:
        m_type = GhostType::DirectChase;
        break;
    default:
        m_type = GhostType::Random;
        break;
    }
}

void model::Ghost::update(const double deltaTime, World& world) {}

GhostMode model::Ghost::getMode() const { return m_mode; }

void model::Ghost::setMode(GhostMode mode) {}

GhostType model::Ghost::getType() const { return m_type; }

int model::Ghost::getId() const { return m_id; }

std::vector<Direction> model::Ghost::getValidDirections(const World& world) const {
    std::vector<Direction> validDirections;

    // lambda helper function
    auto tryDirection = [&](Direction dir) {
        Vec2D step = dirToVector(dir);
        if (world.isMoveValid(m_position, step, *this)) {
            validDirections.push_back(dir);
        }
    };

    tryDirection(Direction::Up);
    tryDirection(Direction::Down);
    tryDirection(Direction::Left);
    tryDirection(Direction::Right);

    return validDirections;
}
Direction model::Ghost::chooseRandomDirection(const std::vector<Direction>& validDirections) {
    if (validDirections.empty()) {
        return m_direction;
    }

    // is current direction valid?
    bool currentDirValid =
        std::find(validDirections.begin(), validDirections.end(), m_direction) != validDirections.end();

    // if more than 2 valid directions we are at a crossroad or junction or if current direction is not valid anymore we
    // need to choose a new direction
    bool atJunction = validDirections.size() > 2 || !currentDirValid;

    // if not at junction and current direction is valid, keep moving in the same direction
    if (!atJunction && currentDirValid) {
        return m_direction;
    }
    // choose new random direction
    return m_direction;
}
void model::Ghost::chooseFacingPacmanDirection(const World& world, const Vec2D& pacmanPos) {}