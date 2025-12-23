#include "GameOverState.h"

#include "../model/Score.h"
#include "MenuState.h"
view::state::GameOverState::GameOverState(StateManager& stateManager, std::shared_ptr<model::Score> playerScore)
    : State(stateManager, playerScore) {}
void view::state::GameOverState::handleEvents(const sf::Event& event) {
    // enter to go bvack to main menu
    // esc to exit game
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Enter:
            // want to play again
            //  reset score
            playerScore->reset();
            stateManager.popState();
            break;
        case sf::Keyboard::Escape:
            //  close window
            stateManager.getWindow().close();
            stateManager.clearStates();
            break;
        }
    }
}
void view::state::GameOverState::update(const double deltaTime) {}
static void centerOrigin(sf::Text& t) {
    sf::FloatRect b = t.getLocalBounds();
    t.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
}
void view::state::GameOverState::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    sf::Font font = util::TextureManager::getScoreFont();

    sf::Text gameOverText("GAME OVER", font, 64);
    gameOverText.setFillColor(sf::Color::Red);
    centerOrigin(gameOverText);

    sf::Text scoreText("SCORE: " + std::to_string(playerScore->getScore()), font, 40);
    scoreText.setFillColor(sf::Color::White);
    centerOrigin(scoreText);

    bool isHighScore = playerScore->isHighScore();
    sf::Text highScoreText("NEW HIGH SCORE!", font, 32);
    highScoreText.setFillColor(sf::Color::White);
    centerOrigin(highScoreText);

    sf::Text instructionsText("ESC TO CLOSE GAME", font, 28);
    sf::Text instructionsText2("ENTER TO RETURN TO MENU", font, 28);
    instructionsText.setFillColor(sf::Color::Cyan);
    instructionsText2.setFillColor(sf::Color::Cyan);
    centerOrigin(instructionsText);
    centerOrigin(instructionsText2);

    const sf::Vector2f c(window.getSize().x / 2.f, window.getSize().y / 2.f);

    // vertical spacing
    float y = c.y - 70.f;
    gameOverText.setPosition(c.x, y);

    y += 70.f;
    scoreText.setPosition(c.x, y);

    if (isHighScore) {
        y += 45.f;
        highScoreText.setPosition(c.x, y);
    }

    y += 90.f;
    instructionsText.setPosition(c.x, y);
    y += 40.f;
    instructionsText2.setPosition(c.x, y);

    window.draw(gameOverText);
    window.draw(scoreText);
    if (isHighScore)
        window.draw(highScoreText);
    window.draw(instructionsText);
    window.draw(instructionsText2);

    window.display();
}