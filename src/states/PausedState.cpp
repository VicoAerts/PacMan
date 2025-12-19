#include "PausedState.h"

#include "../model/Score.h"
view::state::PausedState::PausedState(StateManager& stateManager, model::Score& playerScore)
    : State(stateManager, playerScore) {}
void view::state::PausedState::handleEvents(const sf::Event& event) {
    // resume on esc press
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Escape:
            stateManager.popState();
            // continue clock
            break;
        }
    }
}
void view::state::PausedState::update(const double deltaTime) {}
void view::state::PausedState::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    // Display "Game Over" text
    sf::Font font;
    font = util::TextureManager::getScoreFont();
    sf::Text paused("Game Paused", font, 50);
    sf::Text score("current score: " + std::to_string(playerScore.getScore()), font, 20);
    sf::Text instructions("press esc to resume", font, 10);
    instructions.setFillColor(sf::Color::Cyan);
    paused.setFillColor(sf::Color::Yellow);
    score.setFillColor(sf::Color::White);
    paused.setPosition(window.getSize().x / 2.f - paused.getLocalBounds().width / 2.f,
                       window.getSize().y / 2.f - paused.getLocalBounds().height / 2.f);
    // score just below paused
    score.setPosition(window.getSize().x / 2.f - score.getLocalBounds().width / 2.f,
                      window.getSize().y / 2.f + paused.getLocalBounds().height / 2.f + 10.f);
    instructions.setPosition(window.getSize().x / 2.f - instructions.getLocalBounds().width / 2.f,
                             window.getSize().y / 2.f + paused.getLocalBounds().height / 2.f + 40.f);
    window.draw(score);
    window.draw(paused);
    window.draw(instructions);
    window.display();
}