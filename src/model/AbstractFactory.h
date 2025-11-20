/**
 * @file AbstractFactory.h
 * @brief Declaration of the AbstractFactory class.
 *
 * The abstract factory class serves as a blueprint for creating various game entities.
 *

 */

#ifndef PACMAN_ABSTRACTFACTORY_H
#define PACMAN_ABSTRACTFACTORY_H
#include "Entity.h"
#include <memory>

namespace model {
class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;

    virtual std::unique_ptr<Entity> createPacman(int row, int col) = 0;
    virtual std::unique_ptr<Entity> createGhost(int row, int col) = 0;
    virtual std::unique_ptr<Entity> createCoin(int row, int col) = 0;
    virtual std::unique_ptr<Entity> createFruit(int row, int col) = 0;
    virtual std::unique_ptr<Entity> createWall(int row, int col) = 0;
};
} // namespace model

#endif // PACMAN_ABSTRACTFACTORY_H
