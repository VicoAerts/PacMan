//
// Created by gebruiker on 9/11/2025.
//

#include "LevelState.h"

#include "../../config/config.h"

namespace view::state {
LevelState::LevelState(StateManager& stateManager)
    : State(stateManager), m_factory(stateManager.getWindow()),
      m_camera(Camera(stateManager.getWindow().getSize().x, stateManager.getWindow().getSize().y)) {
    // 1. load maze from file
    // 2. make world
    // 3. make camera
    // 4. create factory

    GridMap map;
    map.loadMazeFromFile("Maze.txt");
    m_world = std::make_unique<model::World>(map, m_factory);
}
void LevelState::handleEvents(const sf::Event& event) {}
void LevelState::update(const double deltaTime) {}
void LevelState::render(sf::RenderWindow& window) { window.clear(sf::Color::Blue); }
} // namespace view::state