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
    next.y = position.y + step.y;
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
        // handle coin
        // if (cell == CellType::COIN) {
        //     pass;
        // }
    }
    return true;
}
void World::snapToCorridor(Vec2D& pos, const Direction dir) const {
    float tileW = 2.f / worldGrid.getWidth();
    float tileH = 2.f / worldGrid.getHeight();

    // current tile
    int col = static_cast<int>((pos.x + 1.f) / tileW);
    int row = static_cast<int>((pos.y + 1.f) / tileH);

    float centerX = -1.f + (col + 0.5f) * tileW;
    float centerY = -1.f + (row + 0.5f) * tileH;

    // offset to middle of tile
    float dx = pos.x - centerX;
    float dy = pos.y - centerY;

    // max offset to still snap
    float maxOffsetX = tileW * 0.35f;
    float maxOffsetY = tileH * 0.35f;

    // avoid jittering by smoothing the snap
    const float pull = 0.25f; // probeer 0.2–0.3
    auto smoothSnap = [pull](float pos, float center) { return pos + (center - pos) * pull; };

    // moving horizontal pulls y to center
    if (dir == Direction::Left || dir == Direction::Right) {
        if (std::fabs(dy) < maxOffsetY) {
            pos.y = smoothSnap(pos.y, centerY);
        }
    }

    // moving vertical pulls x to center
    if (dir == Direction::Up || dir == Direction::Down) {
        if (std::fabs(dx) < maxOffsetX) {
            pos.x = smoothSnap(pos.x, centerX);
        }
    }
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
