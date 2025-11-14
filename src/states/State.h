/**
 * @file State.h
 * @brief Abstract base class for game states.
 */
#ifndef PACMAN_STATE_H
#define PACMAN_STATE_H
#include <SFML/Graphics.hpp>
namespace view::state {
class StateManager; // Forward declaration

class State {
protected:
    StateManager& stateManager;

public:
    /**  constructor */
    explicit State(StateManager& stateManager) : stateManager(stateManager) {}
    /** Virtual destructor to ensure proper cleanup of derived classes */
    virtual ~State() = default;

    /** pure virtual function to handle events in the state */
    virtual void handleEvents() = 0;

    /** pure virtual function to update the state */
    virtual void update(double deltaTime) = 0;

    /** pure virtual function to render the state */
    virtual void render(sf::RenderWindow& window) = 0;
};
} // namespace view::state
#endif // PACMAN_STATE_H
