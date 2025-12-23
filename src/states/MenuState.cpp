
#include "MenuState.h"

#include "../model/Score.h"

namespace view::state {
MenuState::MenuState(StateManager& stateManager, std::shared_ptr<model::Score> playerScore)
    : State(stateManager, playerScore) {
    if (!backgroundTexture.loadFromFile("../assets/pacmenu.png")) {
        throw std::runtime_error("Failed to load assets/pacmenu.png");
    }

    backgroundSprite.setTexture(backgroundTexture);
    util::TextureManager::loadScoreFont();
    m_startButton = sf::RectangleShape();
}

void MenuState::handleEvents(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            // Switch to the playing state when Enter is pressed
            stateManager.pushState(std::make_unique<LevelState>(stateManager, playerScore));
        }
    }
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

        // In jouw render teken je zonder view changes, dus pixel coords = ok
        sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

        if (m_startButton.getGlobalBounds().contains(mousePos)) {
            // Switch to the playing state when the button is clicked
            stateManager.pushState(std::make_unique<LevelState>(stateManager, playerScore));
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

    const auto& scores = playerScore->getHighScores();
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

    // set enter button
    sf::Text startText("or CLICK HERE", util::TextureManager::getScoreFont(),
                       (unsigned int)(24.f * std::min(scaleX, scaleY)));
    startText.setFillColor(sf::Color::White);
    centerOrigin(startText);

    // center button position relative to window size
    sf::Vector2f btnCenter = bgPos(b, 480.f / textureSize.x, 780.f / textureSize.y);
    startText.setPosition(btnCenter);

    // box scales with text size
    sf::FloatRect tb = startText.getLocalBounds();
    float padX = 30.f * std::min(scaleX, scaleY);
    float padY = 18.f * std::min(scaleX, scaleY);

    m_startButton.setSize({tb.width + 2.f * padX, tb.height + 2.f * padY});
    m_startButton.setFillColor(sf::Color::Red);
    m_startButton.setOutlineThickness(3.f * std::min(scaleX, scaleY));
    m_startButton.setOutlineColor(sf::Color::White);

    // center box
    m_startButton.setOrigin(m_startButton.getSize().x / 2.f, m_startButton.getSize().y / 2.f);
    m_startButton.setPosition(btnCenter);

    window.draw(startText);
    window.draw(highScoreText);
    window.draw(score1);
    window.draw(score2);
    window.draw(score3);
    window.draw(score4);
    window.draw(score5);
    window.draw(m_startButton);
    window.draw(startText);

    window.display();
}
} // namespace view::state