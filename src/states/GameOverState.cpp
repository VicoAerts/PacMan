//
// Created by gebruiker on 9/11/2025.
//

#include "GameOverState.h"
view::state::GameOverState::GameOverState(StateManager& stateManager, model::Score& playerScore)
    : State(stateManager, playerScore) {}
void view::state::GameOverState::handleEvents(const sf::Event& event) {}
void view::state::GameOverState::update(const double deltaTime) {}
void view::state::GameOverState::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    // Display "Game Over" text
    sf::Font font;
    font = util::TextureManager::getScoreFont();
    sf::Text gameOverText("Game Over", font, 50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(window.getSize().x / 2.f - gameOverText.getLocalBounds().width / 2.f,
                             window.getSize().y / 2.f - gameOverText.getLocalBounds().height / 2.f);
    window.draw(gameOverText);
    window.display();
}