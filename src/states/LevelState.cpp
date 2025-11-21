//
// Created by gebruiker on 9/11/2025.
//

#include "LevelState.h"

#include "../../config/config.h"

namespace view::state {
LevelState::LevelState(StateManager& stateManager)
    : State(stateManager), m_camera(Camera(stateManager.getWindow().getSize().x, stateManager.getWindow().getSize().y)),
      m_factory(stateManager.getWindow()) {
    // 1. load maze from file
    GridMap map;
    map.loadMazeFromFile("Maze.txt");
    // 2. make world
    m_world = std::make_unique<model::World>(map, m_factory);
    // 3. set camera grid size
    m_camera.setGridSize(map.getHeight(), map.getWidth());
    // 4. get views to render later
    // m_entityViews = m_factory.getviews
}
void LevelState::handleEvents(const sf::Event& event) {}
void LevelState::update(const double deltaTime) {}
void LevelState::render(sf::RenderWindow& window) { window.clear(sf::Color::Blue); }
} // namespace view::state