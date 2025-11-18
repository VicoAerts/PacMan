//
// Created by gebruiker on 9/11/2025.
//

#include "LevelState.h"

namespace view::state {
LevelState::LevelState(StateManager& stateManager) : State(stateManager) {}
void LevelState::handleEvents(const sf::Event& event) {}
void LevelState::update(const double deltaTime) {}
void LevelState::render(sf::RenderWindow& window) {}
} // namespace view::state