//
// Created by gebruiker on 9/11/2025.
//

#include "LevelState.h"

#include "../../config/config.h"
#include "../model/Score.h"
#include "GameOverState.h"

#include <iostream>

namespace view::state {
LevelState::LevelState(StateManager& stateManager, model::Score& playerScore)
    : State(stateManager, playerScore),
      m_camera(Camera(stateManager.getWindow().getSize().x, stateManager.getWindow().getSize().y)),
      m_factory(stateManager.getWindow(), m_camera) {
    // 1. load maze from file
    GridMap map;
    map.loadMazeFromFile("Maze.txt");
    // 2. set camera grid size
    m_camera.setGridSize(map.getHeight(), map.getWidth());

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
    scoreText.setPosition(20.f, 10.f);
}
void LevelState::handleEvents(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            // case esc for pause menu can be added here
        case sf::Keyboard::Left:
            std::cout << "Left" << std::endl;
            m_world->handleInput(Direction::Left);
            break;
        case sf::Keyboard::Right:
            std::cout << "Right" << std::endl;
            m_world->handleInput(Direction::Right);
            break;
        case sf::Keyboard::Up:
            std::cout << "Up" << std::endl;
            m_world->handleInput(Direction::Up);
            break;
        case sf::Keyboard::Down:
            m_world->handleInput(Direction::Down);
            break;
        case sf::Keyboard::K:
            m_world->debugClearCollectables();
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
        // proceed to next level or end game
        stateManager.switchState(std::make_unique<LevelState>(stateManager, playerScore));
        return;
    }
    if (playerScore.isGameOver()) {

        stateManager.switchState(std::make_unique<GameOverState>(stateManager, playerScore));
        return;
    }
}
void LevelState::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    // render all entity views
    for (const auto& v : m_entityViews) {
        v->draw(window, m_camera);
    }
    scoreText.setString("Score: " + std::to_string(playerScore.getScore()));
    window.draw(scoreText);
    window.display();
}
} // namespace view::state