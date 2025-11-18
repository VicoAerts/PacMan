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
class MenuState : public State {
public:
    explicit MenuState(StateManager& stateManager);
    ~MenuState() override = default;

    void handleEvents(const sf::Event& event) override;

    void update(const double deltaTime) override;

    void render(sf::RenderWindow& window) override;

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};
} // namespace view::state

#endif // PACMAN_MENUSTATE_H
