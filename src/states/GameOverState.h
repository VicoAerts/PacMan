/**
 * @file GameOverState.h
 * @brief Declaration of the gameover state class for the Pacman game.
 */
#ifndef PACMAN_GAMEOVERSTATE_H
#define PACMAN_GAMEOVERSTATE_H
#include "../util/TextureManager.h"
#include "State.h"
namespace view::state {
class GameOverState : public State {
public:
    explicit GameOverState(StateManager& stateManager, model::Score& playerScore);
    ~GameOverState() override = default;

    void handleEvents(const sf::Event& event) override;

    void update(const double deltaTime) override;

    void render(sf::RenderWindow& window) override;
};
} // namespace view::state

#endif // PACMAN_GAMEOVERSTATE_H
