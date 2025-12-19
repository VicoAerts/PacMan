//
// Created by gebruiker on 19/12/2025.
//

#include "VictoryState.h"

#include "../model/Score.h"
#include "LevelState.h"
#include "StateManager.h"
view::state::VictoryState::VictoryState(StateManager& stateManager, model::Score& playerScore)
    : State(stateManager, playerScore) {}
void view::state::VictoryState::handleEvents(const sf::Event& event) {
    // enter to proceed to next level
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Enter:
            // proceed to next level
            stateManager.switchState(std::make_unique<view::state::LevelState>(stateManager, playerScore));
            break;
        default:
            break;
        }
    }
}
void view::state::VictoryState::update(const double deltaTime) {}
static void centerOrigin(sf::Text& t) {
    sf::FloatRect b = t.getLocalBounds();
    t.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
}
void view::state::VictoryState::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    sf::Font font = util::TextureManager::getScoreFont();

    sf::Text victoryText("LEVEL COMPLETE!", font, 48);
    victoryText.setFillColor(sf::Color::Green);
    centerOrigin(victoryText);

    sf::Text scoreText("SCORE: " + std::to_string(playerScore.getScore()), font, 40);
    scoreText.setFillColor(sf::Color::White);
    centerOrigin(scoreText);

    sf::Text instructionsText("PRESS ENTER TO CONTINUE", font, 28);
    instructionsText.setFillColor(sf::Color::Cyan);
    centerOrigin(instructionsText);

    const sf::Vector2f c(window.getSize().x / 2.f, window.getSize().y / 2.f);

    // vertical spacing
    float y = c.y - 70.f;
    victoryText.setPosition(c.x, y);
    y += 80.f;
    scoreText.setPosition(c.x, y);
    y += 60.f;
    instructionsText.setPosition(c.x, y);

    window.draw(victoryText);
    window.draw(scoreText);
    window.draw(instructionsText);

    window.display();
}