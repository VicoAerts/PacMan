/**
 * @file GameOverState.h
 * @brief Declaration of the gameover state class for the Pacman game.
 */
#ifndef PACMAN_GAMEOVERSTATE_H
#define PACMAN_GAMEOVERSTATE_H
#include "../util/TextureManager.h"
#include "State.h"
#include "StateManager.h"
namespace view::state {
/**
 * @brief GameOverState class representing the game over screen state.
 *
 * Inherits from the State base class and handles events, updates, and rendering
 * specific to the game over screen.
 */
class GameOverState : public State {
public:
    /** Constructor for GameOverState */
    explicit GameOverState(StateManager& stateManager, std::shared_ptr<model::Score> playerScore);
    /** Destructor for GameOverState */
    ~GameOverState() override = default;
    /** Handle events specific to the game over state */
    void handleEvents(const sf::Event& event) override;
    /** Update the game over state */
    void update(const double deltaTime) override;
    /** Render the game over state */
    void render(sf::RenderWindow& window) override;
};
} // namespace view::state

#endif // PACMAN_GAMEOVERSTATE_H
