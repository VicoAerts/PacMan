/**
 * @file ConcreteFactory.h
 * @brief Concrete Factory for creating game entities and managing the camera.

 */

#ifndef PACMAN_CONCRETEFACTORY_H
#define PACMAN_CONCRETEFACTORY_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "../model/AbstractFactory.h"
#include "../model/Collectable.h"
#include "../model/Entity.h"
#include "../model/Ghost.h"
#include "../model/PacMan.h"
#include "../model/Wall.h"
#include "Camera.h"
namespace view {
class ConcreteFactory : public model::AbstractFactory {
private:
    sf::RenderWindow* m_window;

public:
    /**constructor**/
    explicit ConcreteFactory(sf::RenderWindow& window);

    /** Destructor of the EntityFactory*/
    ~ConcreteFactory() override = default;

    /** override all creations from AbstractFactory */
    std::unique_ptr<model::Entity> createPacman(int row, int col) override;
    std::unique_ptr<model::Entity> createGhost(int row, int col) override;
    std::unique_ptr<model::Entity> createCoin(int row, int col) override;
    std::unique_ptr<model::Entity> createFruit(int row, int col) override;
    std::unique_ptr<model::Entity> createWall(int row, int col) override;
};
} // namespace view

#endif // PACMAN_CONCRETEFACTORY_H
