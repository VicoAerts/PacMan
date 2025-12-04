//
// Created by gebruiker on 20/11/2025.
//

#include "ConcreteFactory.h"

view::ConcreteFactory::ConcreteFactory(sf::RenderWindow& window, Camera& camera) : window(window), camera(camera) {}

std::unique_ptr<model::Entity> view::ConcreteFactory::createPacman(int row, int col) {
    Vec2D pos = camera.gridToWorld(row, col);
    auto model = std::make_unique<model::PacMan>(pos, config::pacman_speed);

    auto view = std::make_unique<view::entity::PacManView>(pos, Direction::None);
    model->attach(*view);
    entityViews.push_back(std::move(view));

    return model;
}

std::unique_ptr<model::Entity> view::ConcreteFactory::createGhost(int row, int col, int ghostId) {
    Vec2D pos = camera.gridToWorld(row, col);
    auto model = std::make_unique<model::Ghost>(pos, config::ghost_base_speed, ghostId);

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
std::unique_ptr<model::Entity> view::ConcreteFactory::createFruit(int row, int col) { return nullptr; }
std::unique_ptr<model::Entity> view::ConcreteFactory::createWall(int row, int col) {
    Vec2D pos = camera.gridToWorld(row, col);
    auto model = std::make_unique<model::Wall>(pos);

    auto view = std::make_unique<view::entity::WallView>(pos);
    model->attach(*view);
    entityViews.push_back(std::move(view));

    return model;
}
