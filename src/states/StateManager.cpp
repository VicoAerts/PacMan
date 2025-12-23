#include "StateManager.h"
#include "../model/Score.h"
#include "MenuState.h"

namespace view::state {
StateManager::StateManager(sf::RenderWindow& window, std::shared_ptr<model::Score> playerScore) : window(window) {
    pushState(std::make_unique<MenuState>(*this, playerScore));
}

// use move because unique_ptr
void StateManager::pushState(std::unique_ptr<State> state) { statesStack.push(std::move(state)); }

void StateManager::popState() {
    if (!statesStack.empty()) {
        statesStack.pop();
    } else {
        throw std::runtime_error("State Stack is empty");
    }
}
void StateManager::switchState(std::unique_ptr<State> state) {
    if (!statesStack.empty()) {
        statesStack.pop();
        statesStack.push(std::move(state));
    }
}
void StateManager::handleEvents(const sf::Event& event) {
    if (!statesStack.empty()) {
        statesStack.top()->handleEvents(event);
    }}
void StateManager::render(sf::RenderWindow& window) {
    if (!statesStack.empty()) {
        statesStack.top()->render(window);
    }
}
void StateManager::update(const double deltaTime) {
    if (!statesStack.empty()) {
        statesStack.top()->update(deltaTime);
    }
}
void StateManager::clearStates() {
    if (statesStack.empty()) {
        return;
    } else {
        while (!statesStack.empty()) {
            statesStack.pop();
        }
    }
}
void StateManager::pop2States() {
    popState();
    popState();
}
} // namespace view::state
