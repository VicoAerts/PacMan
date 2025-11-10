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
        // std::cout << "Delta Time: " << deltaTime << " seconds" << std::endl; //test for clock
        // Process events
        // statemanager.handlevents()
        // render()

        window->display();
    }
}