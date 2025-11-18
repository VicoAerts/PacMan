/**
 * @file LevelState.h
 * @brief Declaration of the LevelState class representing the state of a game level.
 */
#ifndef PACMAN_LEVELSTATE_H
#define PACMAN_LEVELSTATE_H
#include "State.h"
#include "StateManager.h"

namespace view::state {
class LevelState : public State {
public:
    explicit LevelState(StateManager& stateManager);
    ~LevelState() override = default;

    void handleEvents(const sf::Event& event) override;

    void update(const double deltaTime) override;

    void render(sf::RenderWindow& window) override;
};
} // namespace view::state

#endif // PACMAN_LEVELSTATE_H
