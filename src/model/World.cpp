//
// Created by gebruiker on 9/11/2025.
//

#include "World.h"
namespace model {

model::World::World(const GridMap& grid, AbstractFactory& factory) : worldGrid(grid) { spawnEntities(factory); }

void model::World::update(double deltaTime) {
    for (auto& entity : entities) {
        entity->update(deltaTime, *this);
    }
}
void model::World::spawnEntities(AbstractFactory& factory) {
    for (int row = 0; row < worldGrid.getHeight(); row++) {
        for (int col = 0; col < worldGrid.getWidth(); col++) {

            CellType type = worldGrid.getCellType(row, col);

            switch (type) {
            case PACMAN_START:
                entities.push_back(factory.createPacman(row, col));
                break;

            case GHOST_START:
                entities.push_back(factory.createGhost(row, col));
                break;

            case COIN:
                entities.push_back(factory.createCoin(row, col));
                break;

            case FRUIT:
                entities.push_back(factory.createFruit(row, col));
                break;

            case WALL:
                entities.push_back(factory.createWall(row, col));
                break;

            default:
                break;
            }
        }
    }
}
} // namespace model
