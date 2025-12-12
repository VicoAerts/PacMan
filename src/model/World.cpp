//
// Created by gebruiker on 9/11/2025.
//

#include "World.h"

#include "Score.h"

#include <cmath>
#include <iostream>
namespace model {

model::World::World(const GridMap& grid, AbstractFactory& factory, Score& playerScore) : worldGrid(grid) {
    spawnEntities(factory);
    for (auto& entity : entities) {
        entity->attach(playerScore);
    }
    // attach score to pacman as well
    pacMan->attach(playerScore);
}

void model::World::update(double deltaTime) {
    for (auto& entity : entities) {
        entity->update(deltaTime, *this);
    }
    // update pacman separately
    pacMan->update(deltaTime, *this);
}
void World::handleInput(Direction dir) {
    for (auto& entity : entities) {
        entity->handleInput(dir);
    }
    pacMan->handleInput(dir);
}
bool World::isMoveValid(const Vec2D& position, const Vec2D& step, const Entity& entity) const {
    // new position of center of model after move
    Vec2D next;
    next.x = position.x + step.x;
    next.y = position.y + step.y;
    if (next.x < -1.f || next.x > 1.f || next.y < -1.f || next.y > 1.f) {
        std::cerr << "Next position out of world bounds: (" << next.x << ", " << next.y << ")" << std::endl;
        return false;
    }
    // tile size in world coordinates
    float tileW = 2.f / worldGrid.getWidth();
    float tileH = 2.f / worldGrid.getHeight();

    // hitbox half sizes: use same scaling as in the View!

    float halfW = tileW * 0.5f;
    float halfH = tileH * 0.5f;

    // do we move horizontally or vertically?
    bool horizontalMove = (step.x != 0.f);
    bool verticalMove = (step.y != 0.f);
    float halfHScaled = halfH * 0.80f;
    float halfWScaled = halfW * 0.80f;
    std::vector<Vec2D> hitboxPoints;
    if (horizontalMove) {
        bool rightMove = step.x > 0;
        bool leftMove = step.x < 0;
        if (rightMove) {
            // middle
            hitboxPoints.push_back(Vec2D{next.x + halfW, next.y});
            // corners
            hitboxPoints.push_back(Vec2D{next.x + halfW, next.y + halfHScaled});
            hitboxPoints.push_back(Vec2D{next.x + halfW, next.y - halfHScaled});
        }
        if (leftMove) {
            // middle
            hitboxPoints.push_back(Vec2D{next.x - halfW, next.y});
            // corners
            hitboxPoints.push_back(Vec2D{next.x - halfW, next.y + halfHScaled});
            hitboxPoints.push_back(Vec2D{next.x - halfW, next.y - halfHScaled});
        }
    }
    if (verticalMove) {
        bool downMove = step.y > 0;
        bool upMove = step.y < 0;
        if (downMove) {

            hitboxPoints.push_back(Vec2D{next.x, next.y + halfH});
            hitboxPoints.push_back(Vec2D{next.x - halfWScaled, next.y + halfH});
            hitboxPoints.push_back(Vec2D{next.x + halfWScaled, next.y + halfH});
        }
        if (upMove) {
            hitboxPoints.push_back(Vec2D{next.x, next.y - halfH});
            hitboxPoints.push_back(Vec2D{next.x - halfWScaled, next.y - halfH});
            hitboxPoints.push_back(Vec2D{next.x + halfWScaled, next.y - halfH});
        }
    }

    // Check each corner
    for (auto& p : hitboxPoints) {
        CellType cell = worldGrid.getCellType(p.x, p.y);
        if (cell == CellType::WALL) {
            return false;
        }
    }
    return true;
}
void World::snapToCorridor(Vec2D& pos, const Direction dir) const {
    float tileW = 2.f / worldGrid.getWidth();
    float tileH = 2.f / worldGrid.getHeight();

    int col = static_cast<int>((pos.x + 1.f) / tileW);
    int row = static_cast<int>((pos.y + 1.f) / tileH);

    float centerX = -1.f + (col + 0.5f) * tileW;
    float centerY = -1.f + (row + 0.5f) * tileH;

    float dx = pos.x - centerX;
    float dy = pos.y - centerY;

    // max offset
    float maxOffsetX = tileW * 0.35f;
    float maxOffsetY = tileH * 0.35f;

    // MIN offset if its closer than this, no need to snap
    float deadZoneX = tileW * 0.02f;
    float deadZoneY = tileH * 0.02f;

    // smooth snap factor avoid jumpy behavior
    const float pull = 0.25f;
    auto smoothSnap = [pull](float pos, float center) { return pos + (center - pos) * pull; };

    // horizontal movement → y center
    if (dir == Direction::Left || dir == Direction::Right) {
        float ady = std::fabs(dy);

        if (ady <= deadZoneY) {
            // in deadzone no need to snap
        } else if (ady < maxOffsetY) {
            // in snap zone
            pos.y = smoothSnap(pos.y, centerY);
        }
    }

    // vertical movement → x center
    if (dir == Direction::Up || dir == Direction::Down) {
        float adx = std::fabs(dx);

        if (adx <= deadZoneX) {
            // in deadzone no need to snap
        } else if (adx < maxOffsetX) {
            // in snap zone
            pos.x = smoothSnap(pos.x, centerX);
        }
    }
}
void World::handlePacManCollisions(const Vec2D& pos) {
    float tileW = 2.f / worldGrid.getWidth();
    float tileH = 2.f / worldGrid.getHeight();

    // welke tile is het middelpunt van Pacman?
    int col = static_cast<int>((pos.x + 1.f) / tileW);
    int row = static_cast<int>((pos.y + 1.f) / tileH);

    bool pacmanDied = false;

    for (auto& entity : entities) {
        Vec2D ePos = entity->getPosition();
        int eCol = static_cast<int>((ePos.x + 1.f) / tileW);
        int eRow = static_cast<int>((ePos.y + 1.f) / tileH);

        if (eCol == col && eRow == row) {
            events::Event event = entity->onCollideWithPacMan();
            if (event.type == events::EventType::PacManDied) {
                pacmanDied = true;
            }
        }
    }
    if (pacmanDied) {

        if (score.getLives() > 0) {
            resetWorld();
        }
    }
}
Entity& World::getPacMan() const { return *pacMan; }
void World::resetWorld() {
    for (auto& entity : entities) {
        entity->reset();
    }
    pacMan->reset();
}

void model::World::spawnEntities(AbstractFactory& factory) {
    for (int row = 0; row < worldGrid.getHeight(); row++) {
        for (int col = 0; col < worldGrid.getWidth(); col++) {

            CellType type = worldGrid.getCellType(row, col);
            std::unique_ptr<Entity> e;

            switch (type) {
            case PACMAN_START:

                pacMan = factory.createPacman(row, col);
                e = nullptr; // pacman is stored separately
                break;
            case GHOST_START1:
                e = factory.createGhost(row, col, 1);
                break;
            case GHOST_START2:
                e = factory.createGhost(row, col, 2);
                break;
            case GHOST_START3:
                e = factory.createGhost(row, col, 3);
                break;
            case GHOST_START4:
                e = factory.createGhost(row, col, 4);
                break;
            case COIN:
                e = factory.createCoin(row, col);
                break;
            case FRUIT:
                e = factory.createFruit(row, col);
                break;
            case WALL:
                e = factory.createWall(row, col);
                break;
            default:
                break;
            }

            if (e) {
                entities.push_back(std::move(e));
            }
        }
    }
}
} // namespace model
