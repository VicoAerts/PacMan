//
// Created by gebruiker on 9/11/2025.
//

#include "LevelState.h"

#include "../../config/config.h"
#include "../model/Score.h"
#include "GameOverState.h"
#include "PausedState.h"

#include <iostream>

namespace view::state {
LevelState::LevelState(StateManager& stateManager, model::Score& playerScore)
    : State(stateManager, playerScore),
      m_camera(Camera(stateManager.getWindow().getSize().x, stateManager.getWindow().getSize().y)),
      m_factory(stateManager.getWindow(), m_camera, playerScore.getCurrentLevel()) {
    // 1. load maze from file
    GridMap map;
    map.loadMazeFromFile("Maze.txt");
    // 2. set camera grid size
    m_camera.setGridSize(map.getHeight(), map.getWidth());
    // set window size in case of resize
    auto& window = stateManager.getWindow();
    auto curSize = window.getSize();

    float cols = static_cast<float>(map.getWidth());
    float rows = static_cast<float>(map.getHeight());
    float mazeRatio = cols / rows;

    float playH = static_cast<float>(curSize.y) - config::UI_TOP - config::UI_BOTTOM;

    // calc playW based on maze ratio
    float playW = playH * mazeRatio;
    unsigned int windowW = static_cast<unsigned int>(config::UI_LEFT + playW + config::UI_RIGHT);
    unsigned int windowH = static_cast<unsigned int>(config::UI_TOP + playH + config::UI_BOTTOM);

    // apply
    window.setSize({windowW, windowH});
    m_camera.resizeWindow(windowW, windowH);

    // 3. make world
    m_world = std::make_unique<model::World>(map, m_factory, playerScore);

    // 4. set texture manager
    util::TextureManager::init("level", "../assets/sprites.png");
    // 5. get views to render later
    for (auto& entity : m_factory.getEntityViews()) {
        m_entityViews.push_back(std::move(const_cast<std::unique_ptr<view::entity::EntityView>&>(entity)));
    }
    // 6. setup score text
    util::TextureManager::loadScoreFont();
    scoreText.setFont(util::TextureManager::getScoreFont());
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    levelText.setFont(util::TextureManager::getScoreFont());
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color::White);
    livesText.setFont(util::TextureManager::getScoreFont());
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::White);
}
void LevelState::handleEvents(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            // case esc for pause menu can be added here
        case sf::Keyboard::Left:
            m_world->handleInput(Direction::Left);
            break;
        case sf::Keyboard::Right:
            m_world->handleInput(Direction::Right);
            break;
        case sf::Keyboard::Up:
            m_world->handleInput(Direction::Up);
            break;
        case sf::Keyboard::Down:
            m_world->handleInput(Direction::Down);
            break;
        case sf::Keyboard::K:
            m_world->debugClearCollectables();
            break;
        case sf::Keyboard::Escape:
            stateManager.pushState(std::make_unique<PausedState>(stateManager, playerScore));
            break;
        default:
            m_world->handleInput(Direction::None);
        }
    }
}
void LevelState::update(const double deltaTime) {
    if (m_world) {
        m_world->update(deltaTime);
    }
    playerScore.update(deltaTime);
    if (m_world->isWorldCleared()) {
        // proceed to next level

        playerScore.nextLevelSet();
        stateManager.switchState(std::make_unique<LevelState>(stateManager, playerScore));

        return;
    }
    if (playerScore.isGameOver()) {
        // load score in file
        playerScore.saveToFile();
        // switch to game over state
        stateManager.switchState(std::make_unique<GameOverState>(stateManager, playerScore));
        return;
    }
}
// helper functions to set origin of text
static void setOriginLeftTop(sf::Text& t) {
    sf::FloatRect b = t.getLocalBounds();
    t.setOrigin(b.left, b.top);
}

static void setOriginCenterTop(sf::Text& t) {
    sf::FloatRect b = t.getLocalBounds();
    t.setOrigin(b.left + b.width / 2.f, b.top);
}

static void setOriginRightTop(sf::Text& t) {
    sf::FloatRect b = t.getLocalBounds();
    t.setOrigin(b.left + b.width, b.top);
}
void LevelState::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    // render all entity views
    for (const auto& v : m_entityViews) {
        v->draw(window, m_camera);
    }
    const float padX = 25.f;
    const float topY = 10.f;
    const float bottomY = 70.f;

    sf::Font font = util::TextureManager::getScoreFont();

    // TOP: Level
    sf::Text levelText("LEVEL: " + std::to_string(playerScore.getCurrentLevel()), font, 54);
    levelText.setFillColor(sf::Color::White);
    setOriginCenterTop(levelText);
    levelText.setPosition(window.getSize().x / 2.f, topY);

    // BOTTOM LEFT: Score
    sf::Text scoreText("SCORE: " + std::to_string(playerScore.getScore()), font, 20);
    scoreText.setFillColor(sf::Color::White);
    setOriginLeftTop(scoreText);
    scoreText.setPosition(config::UI_LEFT, window.getSize().y - config::UI_BOTTOM + 10.f);

    // BOTTOM RIGHT: Lives
    sf::Text livesText("LIVES: " + std::to_string(playerScore.getLives()), font, 20);
    livesText.setFillColor(sf::Color::White);
    setOriginRightTop(livesText);
    livesText.setPosition(window.getSize().x - config::UI_RIGHT, window.getSize().y - config::UI_BOTTOM + 10.f);

    window.draw(levelText);
    window.draw(scoreText);
    window.draw(livesText);
    window.display();
}
} // namespace view::state