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
} // namespace view::state