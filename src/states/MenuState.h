/**
 * @file MenuState.h
 * @brief Declaration of the MenuState class for the Pacman game.
 */
#ifndef PACMAN_MENUSTATE_H
#define PACMAN_MENUSTATE_H
#include "State.h"

namespace view::state {
class MenuState : public State {
public:
    explicit MenuState(StateManager& stateManager) : State(stateManager) {}
    ~MenuState() override = default;

    void handleEvents() override;

    void update() override;

    void render() override;
};
} // namespace view::state

#endif // PACMAN_MENUSTATE_H
