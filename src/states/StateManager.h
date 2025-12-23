/**
 *@file StateManager.h
 *@brief state manager class uses a stack of states to handle different game states (menu, playing, paused, etc.)
 * this allows implementing the state pattern design pattern.
 */

#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H
#include "State.h"

#include <memory>
#include <stack>

namespace view::state {
/**
 * @brief StateManager class that manages different game states using a stack.
 *
 * The StateManager allows pushing, popping, and switching between different states,
 * such as menu, gameplay, paused, and gameover states.
 */
class StateManager {
    /** stack of states to manage different game states */
    std::stack<std::unique_ptr<State>> statesStack;

    /** allow states to access render window if needed */
    sf::RenderWindow& window;

    std::shared_ptr<model::Score> m_playerScore;

public:
    /** constructor of statemanager that starts of with the menustate*/
    explicit StateManager(sf::RenderWindow& window, std::shared_ptr<model::Score> playerScore);

    /** destructor of statemanager that cleans up all states */
    ~StateManager() = default;

    /** push a new state onto the stack
     * @param state pointer to the new state to be added
     */
    void pushState(std::unique_ptr<State> state);

    /** pop the current state from the stack
     * @return pointer to the removed state
     */
    void popState();

    /** push a new state and remove the current state
     * @param state pointer to the new state to be added
     */
    void switchState(std::unique_ptr<State> state);

    /** handle events by delegating to the current state */
    void handleEvents(const sf::Event& event);

    /** render the current state */
    void render(sf::RenderWindow& window);

    /** update the current state */
    void update(const double deltaTime);

    /** get the render window */
    [[nodiscard]] sf::RenderWindow& getWindow() { return window; }
    /** clear all states from the stack */
    void clearStates();
    /** pop 2 states at once*/
    void pop2States();
};
} // namespace view::state

#endif // PACMAN_STATEMANAGER_H
