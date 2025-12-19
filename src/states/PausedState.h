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
/**
 * @brief PausedState class representing the paused state of the game.
 *
 * Inherits from the State base class and handles events, updates, and rendering
 * specific to the paused state.
 */
class PausedState : public State {
public:
    /** Constructor for PausedState */
    explicit PausedState(StateManager& stateManager, std::shared_ptr<model::Score> playerScore);
    /** Destructor for PausedState */
    ~PausedState() override = default;
    /** Handle events specific to the paused state
     * esc returns to levelstate
     */
    void handleEvents(const sf::Event& event) override;
    /** Update the paused state is unused*/
    void update(const double deltaTime) override;
    /** Render the paused state */
    void render(sf::RenderWindow& window) override;
};
} // namespace view::state

#endif // PACMAN_PAUSEDSTATE_H
