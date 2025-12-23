#include "ConcreteFactory.h"

view::ConcreteFactory::ConcreteFactory(sf::RenderWindow& window, Camera& camera, int currentLevel)
    : window(window), camera(camera), currentLevel(currentLevel) {}

std::unique_ptr<model::PacMan> view::ConcreteFactory::createPacman(int row, int col) {
    Vec2D pos = camera.gridToWorld(row, col);

    auto model = std::make_unique<model::PacMan>(pos, config::pacman_speed);

    auto view = std::make_shared<view::entity::PacManView>(pos, Direction::None);
    model->attach(view);
    entityViews.push_back(view);

    return model;
}

std::unique_ptr<model::Entity> view::ConcreteFactory::createGhost(int row, int col, int ghostId) {
    Vec2D pos = camera.gridToWorld(row, col);
    // calc speed based on level
    int maxLevel = 20;
    int level = std::min(maxLevel, currentLevel);
    float multiplier = 1.0f + 0.02f * (level - 1);

    float speed = config::ghost_base_speed * multiplier;
    auto model = std::make_unique<model::Ghost>(pos, speed, ghostId);

    auto view = std::make_shared<view::entity::GhostView>(pos, ghostId);
    model->attach(view);
    entityViews.push_back(view);
    return model;
}
std::unique_ptr<model::Entity> view::ConcreteFactory::createCoin(int row, int col) {
    Vec2D pos = camera.gridToWorld(row, col);
    auto model = std::make_unique<model::Coin>(pos);

    auto view = std::make_shared<view::entity::CoinView>(pos);
    model->attach(view);
    entityViews.push_back(view);

    return model;
}
std::unique_ptr<model::Entity> view::ConcreteFactory::createFruit(int row, int col) {
    Vec2D pos = camera.gridToWorld(row, col);
    auto model = std::make_unique<model::Fruit>(pos);

    auto view = std::make_shared<view::entity::FruitView>(pos);
    model->attach(view);
    entityViews.push_back(view);

    return model;
}
std::unique_ptr<model::Entity> view::ConcreteFactory::createWall(int row, int col) {
    Vec2D pos = camera.gridToWorld(row, col);
    auto model = std::make_unique<model::Wall>(pos);

    auto view = std::make_shared<view::entity::WallView>(pos);
    model->attach(view);
    entityViews.push_back(view);

    return model;
}
