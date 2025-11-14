//
// Created by gebruiker on 9/11/2025.
//

#include "Game.h"

#include "../model/Clock.h"
#include "../model/World.h"

view::Game::Game() {
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Pacman");
    window->setFramerateLimit(60);
    world = std::make_unique<logic::World>();
}
view::Game::~Game() {}

void view::Game::run() {
    logic::Clock::getInstance()->start();
    while (window->isOpen()) {

        const double deltaTime = logic::Clock::getInstance()->getDeltaTime();
        logic::Clock::getInstance()->start();

        handleEvents();
        update(deltaTime);
        render();
    }
}
void view::Game::close() {
    window->close();
    std::cout << "Game closed" << std::endl;
}
void view::Game::handleEvents() { stateManager->handleEvents(); }
void view::Game::render() {
    window->clear();
    stateManager->render(*window);
    window->display();
}
void view::Game::update(double deltaTime) { stateManager->update(deltaTime); }