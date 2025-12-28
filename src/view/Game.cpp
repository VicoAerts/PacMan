#include "Game.h"

#include "../../config/config.h"
#include "../control/World.h"
#include "../util/Clock.h"

view::Game::Game() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(config::window_width, config::window_height), "Pacman");
    window->setFramerateLimit(config::max_fps);
    playerScore = std::make_shared<model::Score>();
    stateManager = std::make_unique<view::state::StateManager>(*window, playerScore);
}
view::Game::~Game() { window->close(); }

void view::Game::run() {
    util::Clock::getInstance().start();
    while (window->isOpen()) {
        util::Clock::getInstance().tick();
        const double deltaTime = util::Clock::getInstance().getDeltaTime();

        handleEvents();
        update(deltaTime);
        render();
    }
}
void view::Game::close() {
    window->close();
    std::cout << "Game closed" << std::endl;
}
void view::Game::handleEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            close();
        } else if (event.type == sf::Event::Resized) {
            // Zorg dat de view-coördinaten altijd 0..width / 0..height blijven
            sf::View view(
                sf::FloatRect(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height)));
            window->setView(view);
        } else {
            stateManager->handleEvents(event);
        }
    }
}
void view::Game::render() {

    window->clear();
    stateManager->render(*window);
    window->display();
}
void view::Game::update(double deltaTime) { stateManager->update(deltaTime); }