/**
 * @file State.h
 * @brief Abstract base class for game states.
 */
#ifndef PACMAN_STATE_H
#define PACMAN_STATE_H
#include <SFML/Graphics.hpp>
#include <memory>

namespace model {
class Score;
}
/**
 * @namespace view::state
 * @brief Contains all game state classes.
 */
namespace view::state {
class StateManager;
/**
 * @brief Abstract base class for all game states.
 *
 * Defines the interface for handling events, updating, and rendering
 * in different game states (e.g., menu, gameplay, paused, game over).
 */
class State {
protected:
    StateManager& stateManager;
    std::shared_ptr<model::Score> playerScore;

public:
    /**  constructor */
    explicit State(StateManager& stateManager, std::shared_ptr<model::Score> playerScore)
        : stateManager(stateManager), playerScore(playerScore) {}
    /** Virtual destructor to ensure proper cleanup of derived classes */
    virtual ~State() = default;

    /** pure virtual function to handle events in the state */
    virtual void handleEvents(const sf::Event& event) = 0;

    /** pure virtual function to update the state */
    virtual void update(const double deltaTime) = 0;

    /** pure virtual function to render the state */
    virtual void render(sf::RenderWindow& window) = 0;
};
} // namespace view::state
#endif // PACMAN_STATE_H
