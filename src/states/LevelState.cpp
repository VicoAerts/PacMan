//
// Created by gebruiker on 9/11/2025.
//

#include "LevelState.h"

#include "../../config/config.h"

namespace view::state {
LevelState::LevelState(StateManager& stateManager)
    : State(stateManager), m_camera(Camera(stateManager.getWindow().getSize().x, stateManager.getWindow().getSize().y)),
      m_factory(stateManager.getWindow(), m_camera) {
    // 1. load maze from file
    GridMap map;
    map.loadMazeFromFile("Maze.txt");
    // 2. make world
    m_world = std::make_unique<model::World>(map, m_factory);
    // 3. set camera grid size
    m_camera.setGridSize(map.getHeight(), map.getWidth());
    // 4. set texture manager
    util::TextureManager::init("level", "../assets/sprites.png");
    // 4. get views to render later
    for (auto& entity : m_factory.getEntityViews()) {
        m_entityViews.push_back(std::move(const_cast<std::unique_ptr<view::entity::EntityView>&>(entity)));
    }
}
void LevelState::handleEvents(const sf::Event& event) {}
void LevelState::update(const double deltaTime) {
    if (m_world) {
        m_world->update(deltaTime);
    }
}
void LevelState::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    // render all entity views
    for (const auto& v : m_entityViews) {
        v->draw(window, m_camera);
    }
    window.display();
}
} // namespace view::state