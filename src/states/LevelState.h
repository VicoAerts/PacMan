/**
 * @file LevelState.h
 * @brief Declaration of the LevelState class representing the state of a game level.
 */
#ifndef PACMAN_LEVELSTATE_H
#define PACMAN_LEVELSTATE_H
#include "../control/World.h"
#include "../util/TextureManager.h"
#include "../view/ConcreteFactory.h"
#include "../view/EntityView.h"
#include "State.h"
#include "StateManager.h"

namespace view::state {
/**
 * @brief Gameplay state for a single level.
 *
 * Creates a new World when entered, keeps it alive while the level is active,
 * and transitions to other states (pause, victory, game over) via the StateManager.
 */
class LevelState : public State {
public:
    /** Constructor for LevelState
     * sets up everything that is needed to run the level
     * including loading the maze, creating the world,
     * setting up the camera, and preparing entity views for rendering.
     */
    explicit LevelState(StateManager& stateManager, model::Score& playerScore);
    /** Destructor for LevelState */
    ~LevelState() override = default;
    /** Handle events specific to the level state
     * including input from pacman and pausing the game.
     */
    void handleEvents(const sf::Event& event) override;
    /** Update the level state
     * updates the world and camera,
     * checks for level completion or game over conditions,
     * and updates UI elements like score, lives, and level text.
     */
    void update(const double deltaTime) override;
    /** Render the level state
     * draws all entity views and UI elements to the window.
     */
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
    /** level count */
    sf::Text levelText;
    /** lives text to display the player's lives */
    sf::Text livesText;
};
} // namespace view::state

#endif // PACMAN_LEVELSTATE_H
