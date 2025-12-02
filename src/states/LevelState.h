/**
 * @file LevelState.h
 * @brief Declaration of the LevelState class representing the state of a game level.
 */
#ifndef PACMAN_LEVELSTATE_H
#define PACMAN_LEVELSTATE_H
#include "../model/World.h"
#include "../util/TextureManager.h"
#include "../view/ConcreteFactory.h"
#include "../view/EntityView.h"
#include "State.h"
#include "StateManager.h"

namespace view::state {
class LevelState : public State {
public:
    explicit LevelState(StateManager& stateManager, model::Score& playerScore);
    ~LevelState() override = default;

    void handleEvents(const sf::Event& event) override;

    void update(const double deltaTime) override;

    void render(sf::RenderWindow& window) override;

private:
    /** game world for this level */
    std::unique_ptr<model::World> m_world;
    /** camera for this level */
    view::Camera m_camera;
    /** vector of all entity views in this level */
    std::vector<std::unique_ptr<view::entity::EntityView>> m_entityViews;
    /** concrete factory for creating entities */
    view::ConcreteFactory m_factory;
    /** score text to display the player's score */
    sf::Text scoreText;
};
} // namespace view::state

#endif // PACMAN_LEVELSTATE_H
