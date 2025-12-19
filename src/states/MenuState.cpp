
#include "MenuState.h"

#include "../model/Score.h"

namespace view::state {
MenuState::MenuState(StateManager& stateManager, model::Score& playerScore) : State(stateManager, playerScore) {
    if (!backgroundTexture.loadFromFile("../assets/pacmenu.png")) {
        throw std::runtime_error("Failed to load assets/pacmenu.png");
    }

    backgroundSprite.setTexture(backgroundTexture);
    util::TextureManager::loadScoreFont();
}

void MenuState::handleEvents(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            // Switch to the playing state when Enter is pressed
            stateManager.switchState(std::make_unique<LevelState>(stateManager, playerScore));
        }
    }
}
void MenuState::update(const double deltaTime) {}
static void centerOrigin(sf::Text& t) {
    sf::FloatRect b = t.getLocalBounds();
    t.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
}
static sf::Vector2f bgPos(const sf::FloatRect& b, float nx, float ny) {
    // nx, ny in [0..1] relative to background size
    return {b.left + nx * b.width, b.top + ny * b.height};
}

void MenuState::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    // fullscreen scale background
    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();

    float scaleX = (float)windowSize.x / textureSize.x;
    float scaleY = (float)windowSize.y / textureSize.y;

    backgroundSprite.setScale(scaleX, scaleY);
    backgroundSprite.setPosition(0.f, 0.f);

    window.draw(backgroundSprite);

    // get bounds so we can position text relative to background
    sf::FloatRect b = backgroundSprite.getGlobalBounds();

    // scale font size with window size
    unsigned int charSize = (unsigned int)(60.f * std::min(scaleX, scaleY));

    const auto& scores = playerScore.getHighScores();
    // display high score
    sf::Text highScoreText(std::to_string(scores[0]), util::TextureManager::getScoreFont(), charSize);
    highScoreText.setFillColor(sf::Color::White);
    highScoreText.setPosition(bgPos(b, 330.f / textureSize.x, 500.f / textureSize.y));

    // display top 5 scores
    sf::Text score1(std::to_string(scores[0]), util::TextureManager::getScoreFont(), charSize);
    sf::Text score2(std::to_string(scores[1]), util::TextureManager::getScoreFont(), charSize);
    sf::Text score3(std::to_string(scores[2]), util::TextureManager::getScoreFont(), charSize);
    sf::Text score4(std::to_string(scores[3]), util::TextureManager::getScoreFont(), charSize);
    sf::Text score5(std::to_string(scores[4]), util::TextureManager::getScoreFont(), charSize);

    for (auto* t : {&score1, &score2, &score3, &score4, &score5}) {
        t->setFillColor(sf::Color::White);
        centerOrigin(*t);
    }

    score1.setPosition(bgPos(b, 1200.f / textureSize.x, 500.f / textureSize.y));
    score2.setPosition(bgPos(b, 1200.f / textureSize.x, 560.f / textureSize.y));
    score3.setPosition(bgPos(b, 1200.f / textureSize.x, 620.f / textureSize.y));
    score4.setPosition(bgPos(b, 1200.f / textureSize.x, 680.f / textureSize.y));
    score5.setPosition(bgPos(b, 1200.f / textureSize.x, 740.f / textureSize.y));

    window.draw(highScoreText);
    window.draw(score1);
    window.draw(score2);
    window.draw(score3);
    window.draw(score4);
    window.draw(score5);

    window.display();
}
} // namespace view::state