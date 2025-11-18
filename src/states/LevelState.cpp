//
// Created by gebruiker on 9/11/2025.
//

#include "LevelState.h"

namespace view::state {
LevelState::LevelState(StateManager& stateManager) : State(stateManager) {
    // Initialize level state resources here
    // 1. make world
    // 2. make coins walls ghosts pacman etc via AbstractFactory
    // world.initializeLevel();
    // 3. cam opzetten
}
void LevelState::handleEvents(const sf::Event& event) {}
void LevelState::update(const double deltaTime) {}
void LevelState::render(sf::RenderWindow& window) { window.clear(sf::Color::Blue); }
} // namespace view::state