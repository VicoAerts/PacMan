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
        m_spawnDelay = 15.0;
        break;
    }
}

void model::Ghost::update(const double deltaTime, World& world) {
    Vec2D currentPos = m_position;
    m_timeAlive += deltaTime;

    // handle waiting mode
    if (m_waiting) {
        if (m_timeAlive < m_spawnDelay) {
            return;
        }
        m_waiting = false;
        m_mode = GhostMode::Leaving;
    }

    // calculate middle of tile
    float tileW = 2.f / world.getGridMap().getWidth();
    float tileH = 2.f / world.getGridMap().getHeight();
    // calc col and row
    int col = static_cast<int>((currentPos.x + 1.f) / tileW);
    int row = static_cast<int>((1.f - currentPos.y) / tileH);
    float centerX = -1.f + (col + 0.5f) * tileW;
    float centerY = 1.f - (row + 0.5f) * tileH;

    float distToCenter = std::sqrt((currentPos.x - centerX) * (currentPos.x - centerX) +
                                   (currentPos.y - centerY) * (currentPos.y - centerY));
    // make it also working for small delta times
    bool atCenter = distToCenter < (m_speed * deltaTime * 1.5f);

    // check if we already made a decision on this tile
    bool newtile = (col != (int)last_descision_Tile.x || row != (int)last_descision_Tile.y);
    // only choose new direction at center of tile or if no direction is set
    if ((atCenter && newtile) || m_direction == Direction::None) {

        // handle leaving mode
        if (m_mode == GhostMode::Leaving) {
            Vec2D exitPos = world.getGridMap().getExitPosition();
            float distToExit = manhattanDistance(currentPos, exitPos);

            // if we are close to exit, switch to chase mode
            if (distToExit < 0.005f) {
                m_mode = GhostMode::Chase;
                last_descision_Tile = Vec2D{-1.f, -1.f};
            }
        }

        // choose direction to exit if we are not in chase mode yet
        if (m_mode == GhostMode::Leaving) {
            m_direction = getDirectionToTarget(world, world.getGridMap().getExitPosition(), deltaTime);
        }
        if (m_mode == GhostMode::Chase) {
            if (atCenter) {
                currentPos = Vec2D{centerX, centerY};
                setPosition(currentPos);
            }
            switch (m_type) {
            case GhostType::Random:
                m_direction = chooseRandomDirection(world, deltaTime);
                break;
            case GhostType::FacingPacman:
                m_direction = chooseFacingPacmanDirection(world, world.getPacMan().getPosition(), deltaTime);
                break;
            case GhostType::DirectChase:
                m_direction = getDirectionToTarget(world, world.getPacMan().getPosition(), deltaTime);
                break;
            }
            last_descision_Tile = Vec2D{(float)col, (float)row};
        }
    }
    if (m_direction == Direction::None) {
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
    }
}

GhostMode model::Ghost::getMode() const { return m_mode; }

void model::Ghost::setMode(GhostMode mode) { m_mode = mode; }

GhostType model::Ghost::getType() const { return m_type; }

int model::Ghost::getId() const { return m_id; }

std::vector<Direction> model::Ghost::getValidDirections(const World& world, double deltaTime) const {
    std::vector<Direction> validDirections;
    const GridMap& grid = world.getGridMap();
    float tileW = 2.f / grid.getWidth();
    float tileH = 2.f / grid.getHeight();
    int col = static_cast<int>((m_position.x + 1.f) / tileW);
    int row = static_cast<int>((1.f - m_position.y) / tileH);

    // lambda helper function
    auto tryDirection = [&](Direction dir, int dRow, int dCol) {
        int nextRow = row + dRow;
        int nextCol = col + dCol;
        // check bounds
        if (grid.inBounds(nextRow, nextCol)) {
            CellType type = grid.getCellType(nextRow, nextCol);
            if (type == CellType::WALL)
                return;
            if (type == CellType::EXIT && m_mode == GhostMode::Chase)
                return;
            validDirections.push_back(dir);
        }
    };

    tryDirection(Direction::Up, -1, 0);
    tryDirection(Direction::Down, 1, 0);
    tryDirection(Direction::Left, 0, -1);
    tryDirection(Direction::Right, 0, 1);

    return validDirections;
}
Direction model::Ghost::chooseRandomDirection(World& world, double deltaTime) const {

    auto validDirections = getValidDirections(world, deltaTime);

    // choose new random direction
    // remove opposite direction to avoid going back
    if (validDirections.size() > 1 && m_direction != Direction::None) {
        Direction oppositeDir = opposite(m_direction);
        validDirections.erase(std::remove(validDirections.begin(), validDirections.end(), oppositeDir),
                              validDirections.end());
    }

    if (validDirections.empty()) {
        // only option is to go back if stuck
        return (m_direction != Direction::None) ? opposite(m_direction) : Direction::None;
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
    // scale to 1 tile
    float tileW = 2.f / world.getGridMap().getWidth();
    float tileH = 2.f / world.getGridMap().getHeight();
    // look 4 tiles ahead
    pacStep.x *= tileW * 4.f;
    pacStep.y *= tileH * 4.f;

    Vec2D pacAheadPos = pacmanPos;
    pacAheadPos.x += pacStep.x;
    pacAheadPos.y += pacStep.y;

    return getDirectionToTarget(world, pacAheadPos, deltaTime);
}
void model::Ghost::setDirection(Direction dir) {
    m_direction = dir;
    notify(events::Event{events::EventType::DirectionChanged, getDirection()}, *this);
}
Direction model::Ghost::getDirectionToTarget(World& world, const Vec2D& targetPos, double deltaTime) const {
    auto validDirections = getValidDirections(world, deltaTime);

    if (validDirections.empty())
        return m_direction;

    // remove opposite direction to avoid going back
    if (validDirections.size() > 1 && m_direction != Direction::None) {
        Direction back = opposite(m_direction);
        auto it = std::remove(validDirections.begin(), validDirections.end(), back);
        if (it != validDirections.end()) {
            validDirections.erase(it, validDirections.end());
        }
    }

    float tileW = 2.f / world.getGridMap().getWidth();
    float tileH = 2.f / world.getGridMap().getHeight();

    // initialize best distance at infinity
    float bestDist = std::numeric_limits<float>::infinity();
    std::vector<Direction> bestCandidates; // list to hold equally good directions

    for (Direction dir : validDirections) {
        Vec2D step = dirToVector(dir);
        Vec2D nextPos = m_position;

        // Scale step to 1 tile
        nextPos.x += step.x * tileW;
        nextPos.y += step.y * tileH;

        // Manhattan distance calculation
        float dist = manhattanDistance(nextPos, targetPos);
        // Epsilon for floating point comparison
        const float epsilon = 1e-6f;

        // chek if this distance is better than the best distance
        if (dist < bestDist - epsilon) {
            bestDist = dist;
            bestCandidates.clear();        // throw away previous best candidates
            bestCandidates.push_back(dir); // add this direction as the new best
        }
        // if distances are equal within epsilon, add to candidates
        else if (std::abs(dist - bestDist) < epsilon) {
            bestCandidates.push_back(dir);
        }
    }

    // Safety check - should not happen
    if (bestCandidates.empty())
        return m_direction;

    // If multiple best candidates, choose one at random
    if (bestCandidates.size() > 1) {
        int randomIndex = world.rng.randomInt(0, (int)bestCandidates.size() - 1);
        return bestCandidates[randomIndex];
    }

    // if only one best candidate, return it
    return bestCandidates[0];
}