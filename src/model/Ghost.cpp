//
// Created by gebruiker on 18/11/2025.
//

#include "Ghost.h"

#include <iostream>
float manhattanDistance(const Vec2D& a, const Vec2D& b) { return std::fabs(a.x - b.x) + std::fabs(a.y - b.y); }

model::Ghost::Ghost(const Vec2D& startpos, float speed, int ghostId)
    : Entity(startpos), m_speed(speed), m_direction(Direction::None), m_mode(GhostMode::Chase), m_startpos(startpos),
      m_id(ghostId) {
    switch (ghostId) {
    case 1:
        m_type = GhostType::Random;
        m_spawnDelay = 0.0;
        break;
    case 2:
        m_type = GhostType::FacingPacman;
        m_spawnDelay = 0.0;
        break;
    case 3:
        m_type = GhostType::FacingPacman;
        m_spawnDelay = 5.0;
        break;
    case 4:
        m_type = GhostType::DirectChase;
        m_spawnDelay = 10.0;
        break;
    default:
        m_type = GhostType::Random;
        m_spawnDelay = 0.0;
        break;
    }
}

void model::Ghost::update(const double deltaTime, World& world) {
    Vec2D currentPos = m_position;
    m_timeAlive += deltaTime;
    if (m_waiting) {
        if (m_timeAlive < m_spawnDelay) {
            return;
        }
        m_waiting = false;
    }
    std::cout << "Ghost " << m_id << " is waiting " << m_waiting << std::endl;

    if (m_mode == GhostMode::Chase) {
        switch (m_type) {
        case GhostType::Random:
            m_direction = chooseRandomDirection(world, deltaTime);
            break;
        case GhostType::FacingPacman:
            m_direction = chooseFacingPacmanDirection(world, world.getPacMan().getPosition(), deltaTime);
            break;
        case GhostType::DirectChase:
            m_direction = chooseRandomDirection(world, deltaTime);
            break;
        }
    }
    if (m_direction == Direction::None) {
        std::cout << "Ghost " << m_id << " has no direction to move in." << std::endl;
        return;
    }
    // movement
    // snap to corridor before moving
    world.snapToCorridor(currentPos, m_direction);
    setPosition(currentPos);
    Vec2D dirVec = dirToVector(m_direction);
    float scale = m_speed * deltaTime;

    Vec2D move;
    move.x = dirVec.x * scale;
    move.y = dirVec.y * scale;

    if (move.x == 0.f && move.y == 0.f) {
        return;
    }

    if (world.isMoveValid(m_position, move, *this)) {
        currentPos.x += move.x;
        currentPos.y += move.y;

        world.snapToCorridor(currentPos, m_direction);
        setPosition(currentPos);
        std::cout << "Ghost " << m_id << " moved" << std::endl;
    } else {
        // we hit a wall, stop moving
        m_direction = Direction::None;
    }
}

GhostMode model::Ghost::getMode() const { return m_mode; }

void model::Ghost::setMode(GhostMode mode) {}

GhostType model::Ghost::getType() const { return m_type; }

int model::Ghost::getId() const { return m_id; }

std::vector<Direction> model::Ghost::getValidDirections(const World& world, double deltaTime) const {
    std::vector<Direction> validDirections;
    Vec2D currentPos = m_position;
    // world.snapToCorridor(currentPos, m_direction);

    // lambda helper function
    auto tryDirection = [&](Direction dir) {
        Vec2D dirVec = dirToVector(dir);
        float scale = m_speed * deltaTime;

        Vec2D move;
        move.x = dirVec.x * scale;
        move.y = dirVec.y * scale;

        if (move.x == 0.f && move.y == 0.f) {
            return;
        }

        if (world.isMoveValid(currentPos, move, *this)) {
            validDirections.push_back(dir);
        }
    };

    tryDirection(Direction::Up);
    tryDirection(Direction::Down);
    tryDirection(Direction::Left);
    tryDirection(Direction::Right);

    return validDirections;
}
Direction model::Ghost::chooseRandomDirection(World& world, double deltaTime) const {

    auto validDirections = getValidDirections(world, deltaTime);

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

    // 50% chance to keep moving in the same direction if possible
    // with coinflip
    if (currentDirValid) {
        int coin = world.rng.randomInt(0, 1);
        if (coin == 0) {
            return m_direction;
        }
    }
    // choose new random direction
    // remove current direction and its opposite from valid directions to avoid going back when other options exist
    Direction oppositeDir = opposite(m_direction);
    validDirections.erase(std::remove(validDirections.begin(), validDirections.end(), oppositeDir),
                          validDirections.end());
    validDirections.erase(std::remove(validDirections.begin(), validDirections.end(), m_direction),
                          validDirections.end());
    if (validDirections.empty()) {
        // only option is to go back
        return oppositeDir;
    }

    int randomIndex = world.rng.randomInt(0, (int)validDirections.size() - 1);
    return validDirections[randomIndex];
}
Direction model::Ghost::chooseFacingPacmanDirection(World& world, const Vec2D& pacmanPos, double deltaTime) const {
    auto validDirections = getValidDirections(world, deltaTime);

    if (validDirections.empty()) {
        return m_direction;
    }

    Vec2D ghostPos = m_position;
    // look 1 tile ahead of pacman
    Direction pacmanDir = world.getPacMan().getDirection();
    Vec2D pacStep = dirToVector(pacmanDir);

    Vec2D pacAheadPos = pacmanPos;
    pacAheadPos.x += pacStep.x;
    pacAheadPos.y += pacStep.y;

    // initilize on inf distance
    float bestDist = std::numeric_limits<float>::infinity();
    std::vector<Direction> best;

    for (Direction dir : validDirections) {
        Vec2D step = dirToVector(dir);
        Vec2D newPos = ghostPos;
        newPos.x += step.x;
        newPos.y += step.y;
        float dist = manhattanDistance(newPos, pacAheadPos);
        if (dist < bestDist - 1e-6f) {
            bestDist = dist;
            best.clear();
            best.push_back(dir);

        } else if (std::fabs(dist - bestDist) < 1e-6f) {
            best.push_back(dir);
        }
    }
    // safety shouldnt happen
    if (best.empty()) {
        return m_direction;
    }

    int randomIndex = world.rng.randomInt(0, (int)best.size() - 1);
    return best[randomIndex];
}