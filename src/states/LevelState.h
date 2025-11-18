/**
 * @file LevelState.h
 * @brief Declaration of the LevelState class representing the state of a game level.
 */
#ifndef PACMAN_LEVELSTATE_H
#define PACMAN_LEVELSTATE_H
#include "../model/Camera.h"
#include "../model/World.h"
#include "../view/EntityView.h"
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

private:
    /** game world for this level */
    model::World m_world;
    /** camera for this level */
    model::Camera m_camera;
    /** vector of all entity views in this level */
    std::vector<std::unique_ptr<view::entity::EntityView>> m_entityViews;
};
} // namespace view::state

#endif // PACMAN_LEVELSTATE_H
