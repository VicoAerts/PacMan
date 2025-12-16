/**
 * @file PausedState.h
 * @brief Definition of the PausedState class representing the paused state in the game.
 */
#ifndef PACMAN_PAUSEDSTATE_H
#define PACMAN_PAUSEDSTATE_H
#include "../util/TextureManager.h"
#include "State.h"
#include "StateManager.h"

namespace view::state {
class PausedState : public State {
public:
    explicit PausedState(StateManager& stateManager, model::Score& playerScore);
    ~PausedState() override = default;

    void handleEvents(const sf::Event& event) override;

    void update(const double deltaTime) override;

    void render(sf::RenderWindow& window) override;
};
} // namespace view::state

#endif // PACMAN_PAUSEDSTATE_H
