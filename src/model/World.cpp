//
// Created by gebruiker on 9/11/2025.
//

#include "World.h"

#include <cmath>
#include <iostream>
namespace model {

model::World::World(const GridMap& grid, AbstractFactory& factory) : worldGrid(grid) { spawnEntities(factory); }

void model::World::update(double deltaTime) {
    for (auto& entity : entities) {
        entity->update(deltaTime, *this);
    }
}
void World::handleInput(Direction dir) {
    // avoid Pacman*
    for (auto& entity : entities) {
        try {
            // cast to refernece
            PacMan& pac = dynamic_cast<PacMan&>(*entity);
            pac.setRequestedDirection(dir);
            return;
        } catch (const std::bad_cast&) {
            // this is no Pacman, continue searching
        }
    }
}
bool World::isMoveValid(const Vec2D& position, const Vec2D& step, const Entity& entity) const {
    // new position of center of model after move
    Vec2D next;
    next.x = position.x + step.x;
    next.y = position.y - step.y;
    // tile size in world coordinates
    float tileW = 2.f / worldGrid.getWidth();
    float tileH = 2.f / worldGrid.getHeight();

    // hitbox half sizes: use same scaling as in the View!

    float halfW = tileW * 0.5f;
    float halfH = tileH * 0.5f;

    // do we move horizontally or vertically?
    bool horizontalMove = (step.x != 0.f);
    bool verticalMove = (step.y != 0.f);

    std::vector<Vec2D> hitboxPoints;

    if (horizontalMove) {
        bool rightMove = step.x > 0;
        bool leftMove = step.x < 0;
        if (rightMove) {
            hitboxPoints.push_back(Vec2D{next.x + halfW, next.y});
        }
        if (leftMove) {
            hitboxPoints.push_back(Vec2D{next.x - halfW, next.y});
        }
    }
    if (verticalMove) {
        bool downMove = step.y > 0;
        bool upMove = step.y < 0;
        if (downMove) {
            hitboxPoints.push_back(Vec2D{next.x, next.y + halfH});
        }
        if (upMove) {
            hitboxPoints.push_back(Vec2D{next.x, next.y - halfH});
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

void model::World::spawnEntities(AbstractFactory& factory) {
    for (int row = 0; row < worldGrid.getHeight(); row++) {
        for (int col = 0; col < worldGrid.getWidth(); col++) {

            CellType type = worldGrid.getCellType(row, col);
            std::unique_ptr<Entity> e;

            switch (type) {
            case PACMAN_START:

                e = factory.createPacman(row, col);
                break;
            case GHOST_START:
                e = factory.createGhost(row, col);
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

            if (e) { // ⬅️ alleen als niet null
                entities.push_back(std::move(e));
            }
        }
    }
}
} // namespace model
