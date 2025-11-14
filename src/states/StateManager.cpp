//
// Created by gebruiker on 10/11/2025.
//

#include "StateManager.h"
#include "MenuState.h"

namespace view::state {

StateManager::StateManager() { pushState(std::make_unique<MenuState>(*this)); }

// use move because unique_ptr
void StateManager::pushState(std::unique_ptr<State> state) { statesStack.push(std::move(state)); }

void StateManager::popState() {
    if (!statesStack.empty()) {
        statesStack.pop();
    } else {
        // Handle the case where there are no states to pop
        // throw exception ofzo
    }
}
void StateManager::switchState(std::unique_ptr<State> state) {
    if (!statesStack.empty()) {
        statesStack.pop();
        statesStack.push(std::move(state));
    } else {
        // Handle the case where there are no states to switch
        // throw exception ofzo
    }
}
void StateManager::handleEvents() {
    if (!statesStack.empty()) {
        statesStack.top()->handleEvents();
    } else {
        // Handle the case where there are no states to handle events
        // throw exception ofzo
    }
}
void StateManager::render(sf::RenderWindow& window) {
    if (!statesStack.empty()) {
        statesStack.top()->render(window);
    } else {
        // Handle the case where there are no states to render
        // throw exception ofzo
    }
}
void StateManager::update(double deltaTime) {
    if (!statesStack.empty()) {
        statesStack.top()->update(deltaTime);
    } else {
        // Handle the case where there are no states to handle events
        // throw exception ofzo
    }
}
} // namespace view::state