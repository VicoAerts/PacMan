//
// Created by gebruiker on 9/11/2025.
//

#include "LevelState.h"

#include "../../config/config.h"

namespace view::state {
LevelState::LevelState(StateManager& stateManager) : State(stateManager), m_factory(stateManager.getWindow()) {

    // 1. make world check
    // 2. make coins walls ghosts pacman etc via AbstractFactory
    // world.initializeLevel();
    // 3. cam opzetten
    // map laden
    GridMap map;
    map.loadMazeFromFile("Maze.txt");
    m_world = std::make_unique<model::World>(map, m_factory);
}
void LevelState::handleEvents(const sf::Event& event) {}
void LevelState::update(const double deltaTime) {}
void LevelState::render(sf::RenderWindow& window) { window.clear(sf::Color::Blue); }
} // namespace view::state