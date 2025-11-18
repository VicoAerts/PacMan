//
// Created by gebruiker on 9/11/2025.
//
#include "MenuState.h"

namespace view::state {
MenuState::MenuState(StateManager& stateManager) : State(stateManager) {
    if (!backgroundTexture.loadFromFile("../assets/pacmenu.png")) {
        throw std::runtime_error("Failed to load assets/pacmenu.png");
    }

    backgroundSprite.setTexture(backgroundTexture);
}

void MenuState::handleEvents(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            // Switch to the playing state when Enter is pressed
            stateManager.switchState(std::make_unique<LevelState>(stateManager));
        }
    }
}
void MenuState::update(const double deltaTime) {}
void MenuState::render(sf::RenderWindow& window) {
    // FULLSCREEN SCALE
    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();

    float scaleX = (float)windowSize.x / textureSize.x;
    float scaleY = (float)windowSize.y / textureSize.y;

    backgroundSprite.setScale(scaleX, scaleY);
    backgroundSprite.setPosition(0.f, 0.f);
    window.draw(backgroundSprite);
}
} // namespace view::state