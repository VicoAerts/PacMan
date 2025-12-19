/**
 * @file MenuState.h
 * @brief Declaration of the MenuState class for the Pacman game.
 */
#ifndef PACMAN_MENUSTATE_H
#define PACMAN_MENUSTATE_H
#include "LevelState.h"
#include "State.h"
#include "StateManager.h"
#include <memory>

namespace view::state {
/**
 * @brief MenuState class representing the main menu state.
 *
 * Inherits from the State base class and handles events, updates, and rendering
 * specific to the main menu screen.
 */
class MenuState : public State {
public:
    /** Constructor for MenuState */
    explicit MenuState(StateManager& stateManager, model::Score& playerScore);
    /** Destructor for MenuState */
    ~MenuState() override = default;
    /** Handle events specific to the menu state
     * more specifically enter starts game
     */
    void handleEvents(const sf::Event& event) override;
    /** Update the menu state is unused*/
    void update(const double deltaTime) override;
    /** Render the menu state */
    void render(sf::RenderWindow& window) override;

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};
} // namespace view::state

#endif // PACMAN_MENUSTATE_H
