/**
 * @file ConcreteFactory.h
 * @brief Concrete Factory for creating views and game entities.

 */

#ifndef PACMAN_CONCRETEFACTORY_H
#define PACMAN_CONCRETEFACTORY_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "../../config/config.h"
#include "../model/AbstractFactory.h"
#include "../model/Coin.h"
#include "../model/Collectable.h"
#include "../model/Entity.h"
#include "../model/Fruit.h"
#include "../model/Ghost.h"
#include "../model/PacMan.h"
#include "../model/Wall.h"
#include "../util/Vec2D.h"
#include "Camera.h"
#include "CoinView.h"
#include "EntityView.h"
#include "FruitView.h"
#include "GhostView.h"
#include "PacManView.h"
#include "WallView.h"
/**
 * @namespace view
 * @brief Contains all classes related to the game view and rendering.
 * This namespace is responsible for displaying the game entities
 * and managing the visual aspects of the game.
 */
namespace view {
/** @brief Concrete Factory class for creating game entities and their views */
class ConcreteFactory : public model::AbstractFactory {
private:
    sf::RenderWindow& window;
    Camera& camera;
    std::vector<std::shared_ptr<entity::EntityView>> entityViews;
    // keep track of current level to make levels harder
    int currentLevel;

public:
    /**constructor**/
    explicit ConcreteFactory(sf::RenderWindow& window, Camera& camera, int currentLevel);

    /** Destructor of the EntityFactory*/
    ~ConcreteFactory() override = default;

    /** override all creations from AbstractFactory */
    std::unique_ptr<model::PacMan> createPacman(int row, int col) override;
    std::unique_ptr<model::Entity> createGhost(int row, int col, int ghostId) override;
    std::unique_ptr<model::Entity> createCoin(int row, int col) override;
    std::unique_ptr<model::Entity> createFruit(int row, int col) override;
    std::unique_ptr<model::Entity> createWall(int row, int col) override;

    /** Get all entity views created by this factory */
    [[nodiscard]] const std::vector<std::shared_ptr<entity::EntityView>>& getEntityViews() const { return entityViews; }
};
} // namespace view

#endif // PACMAN_CONCRETEFACTORY_H
