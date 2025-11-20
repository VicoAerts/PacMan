/**
 * @file World.h
 * @brief holds all entities, orchestration of game logic and interaction between entities
 */

#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H
#include "AbstractFactory.h"
#include "Entity.h"
#include "GridMap.h"
#include <memory>
#include <vector>

namespace model {
class World {
public:
    World(const GridMap& map, AbstractFactory& factory);

    void update(double deltaTime);

    [[nodiscard]] const GridMap& getGridMap() const { return worldGrid; }

private:
    GridMap worldGrid;
    // Other members like entities, score, lives, etc.
    std::vector<std::unique_ptr<Entity>> entities;

    void spawnEntities(AbstractFactory& factory);
};
} // namespace model
#endif // PACMAN_WORLD_H
