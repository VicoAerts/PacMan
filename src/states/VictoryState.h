/**
 * @file VictoryState.h
 * @brief Declaration of the VictoryState class representing the victory state in the game.
 */
#ifndef PACMAN_VICTORYSTATE_H
#define PACMAN_VICTORYSTATE_H
#include "State.h"

namespace view::state {
/**
 * @brief VictoryState class representing the victory screen state.
 *
 * Inherits from the State base class and handles events, updates, and rendering
 * specific to the victory screen.
 */
class VictoryState : public State {
public:
    /** Constructor for VictoryState */
    explicit VictoryState(StateManager& stateManager, model::Score& playerScore);
    /** Destructor for VictoryState */
    ~VictoryState() override = default;
    /** Handle events specific to the victory state */
    void handleEvents(const sf::Event& event) override;
    /** Update the victory state */
    void update(const double deltaTime) override;
    /** Render the victory state */
    void render(sf::RenderWindow& window) override;
};

} // namespace view::state
#endif // PACMAN_VICTORYSTATE_H
