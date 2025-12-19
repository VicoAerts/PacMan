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
void StateManager::handleEvents(const sf::Event& event) {
    if (!statesStack.empty()) {
        statesStack.top()->handleEvents(event);
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
void StateManager::update(const double deltaTime) {
    if (!statesStack.empty()) {
        statesStack.top()->update(deltaTime);
    } else {
        // Handle the case where there are no states to handle events
        // throw exception ofzo
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
} // namespace view::state
