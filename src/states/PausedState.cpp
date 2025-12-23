#include "PausedState.h"

#include "../model/Score.h"
view::state::PausedState::PausedState(StateManager& stateManager, std::shared_ptr<model::Score> playerScore)
    : State(stateManager, playerScore) {}
void view::state::PausedState::handleEvents(const sf::Event& event) {
    // resume on esc press
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Escape:
            stateManager.pop2States();
            break;

        case sf::Keyboard::Enter:
            stateManager.popState();
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
    sf::Text score("current score: " + std::to_string(playerScore->getScore()), font, 20);
    sf::Text instructions("press enter to resume", font, 10);
    sf::Text instruction2("press esc to return to menu", font, 10);
    instructions.setFillColor(sf::Color::Cyan);
    instruction2.setFillColor(sf::Color::Cyan);
    paused.setFillColor(sf::Color::Yellow);
    score.setFillColor(sf::Color::White);
    paused.setPosition(window.getSize().x / 2.f - paused.getLocalBounds().width / 2.f,
                       window.getSize().y / 2.f - paused.getLocalBounds().height / 2.f);
    // score just below paused
    score.setPosition(window.getSize().x / 2.f - score.getLocalBounds().width / 2.f,
                      window.getSize().y / 2.f + paused.getLocalBounds().height / 2.f + 10.f);
    instructions.setPosition(window.getSize().x / 2.f - instructions.getLocalBounds().width / 2.f,
                             window.getSize().y / 2.f + paused.getLocalBounds().height / 2.f + 40.f);
    instruction2.setPosition(window.getSize().x / 2.f - instruction2.getLocalBounds().width / 2.f,
                             window.getSize().y / 2.f + paused.getLocalBounds().height / 2.f + 55.f);
    window.draw(score);
    window.draw(paused);
    window.draw(instructions);
    window.draw(instruction2);
    window.display();
}