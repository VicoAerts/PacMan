//
// Created by gebruiker on 20/11/2025.
//

#include "ConcreteFactory.h"

view::ConcreteFactory::ConcreteFactory(sf::RenderWindow& window, Camera& camera, int currentLevel)
    : window(window), camera(camera), currentLevel(currentLevel) {}

std::unique_ptr<model::PacMan> view::ConcreteFactory::createPacman(int row, int col) {
    Vec2D pos = camera.gridToWorld(row, col);
    // calc speed based on level
    float multiplier = 1.0f + 0.06f * (currentLevel - 1);
    if (multiplier > 1.25f)
        multiplier = 1.25f; // cap max speed increase to keep game playable

    float speed = config::pacman_speed * multiplier;
    auto model = std::make_unique<model::PacMan>(pos, speed);

    auto view = std::make_unique<view::entity::PacManView>(pos, Direction::None);
    model->attach(*view);
    entityViews.push_back(std::move(view));

    return model;
}

std::unique_ptr<model::Entity> view::ConcreteFactory::createGhost(int row, int col, int ghostId) {
    Vec2D pos = camera.gridToWorld(row, col);
    // calc speed based on level
    float multiplier = 1.0f + 0.05f * (currentLevel - 1);
    if (multiplier > 1.27f)
        multiplier = 1.27f;

    float speed = config::ghost_base_speed * multiplier;
    auto model = std::make_unique<model::Ghost>(pos, speed, ghostId);

    auto view = std::make_unique<view::entity::GhostView>(pos, ghostId);
    model->attach(*view);
    entityViews.push_back(std::move(view));
    return model;
}
std::unique_ptr<model::Entity> view::ConcreteFactory::createCoin(int row, int col) {
    Vec2D pos = camera.gridToWorld(row, col);
    auto model = std::make_unique<model::Coin>(pos);

    auto view = std::make_unique<view::entity::CoinView>(pos);
    model->attach(*view);
    entityViews.push_back(std::move(view));

    return model;
}
std::unique_ptr<model::Entity> view::ConcreteFactory::createFruit(int row, int col) {
    Vec2D pos = camera.gridToWorld(row, col);
    auto model = std::make_unique<model::Fruit>(pos);

    auto view = std::make_unique<view::entity::FruitView>(pos);
    model->attach(*view);
    entityViews.push_back(std::move(view));

    return model;
}
std::unique_ptr<model::Entity> view::ConcreteFactory::createWall(int row, int col) {
    Vec2D pos = camera.gridToWorld(row, col);
    auto model = std::make_unique<model::Wall>(pos);

    auto view = std::make_unique<view::entity::WallView>(pos);
    model->attach(*view);
    entityViews.push_back(std::move(view));

    return model;
}
