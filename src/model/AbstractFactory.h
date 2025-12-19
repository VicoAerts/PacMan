/**
 * @file AbstractFactory.h
 * @brief Declaration of the AbstractFactory class.
 *
 * The abstract factory class serves as a blueprint for creating various game entities.
 * This class is part of the Abstract Factory design pattern.
 *

 */

#ifndef PACMAN_ABSTRACTFACTORY_H
#define PACMAN_ABSTRACTFACTORY_H
#include <memory>

namespace model {
class Entity;
class PacMan;
} // namespace model

namespace model {
class AbstractFactory {
public:
    /** Virtual destructor */
    virtual ~AbstractFactory() = default;

    /** Pure virtual methods for creating game entities */
    virtual std::unique_ptr<PacMan> createPacman(int row, int col) = 0;
    virtual std::unique_ptr<Entity> createGhost(int row, int col, int ghostId) = 0;
    virtual std::unique_ptr<Entity> createCoin(int row, int col) = 0;
    virtual std::unique_ptr<Entity> createFruit(int row, int col) = 0;
    virtual std::unique_ptr<Entity> createWall(int row, int col) = 0;
};
} // namespace model

#endif // PACMAN_ABSTRACTFACTORY_H
