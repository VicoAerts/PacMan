//
// Created by gebruiker on 20/11/2025.
//

#include "ConcreteFactory.h"
view::ConcreteFactory::ConcreteFactory(sf::RenderWindow& window) {}
std::unique_ptr<model::Entity> view::ConcreteFactory::createPacman(int row, int col) { return nullptr; }
std::unique_ptr<model::Entity> view::ConcreteFactory::createGhost(int row, int col) { return nullptr; }
std::unique_ptr<model::Entity> view::ConcreteFactory::createCoin(int row, int col) { return nullptr; }
std::unique_ptr<model::Entity> view::ConcreteFactory::createFruit(int row, int col) { return nullptr; }
std::unique_ptr<model::Entity> view::ConcreteFactory::createWall(int row, int col) { return nullptr; }
