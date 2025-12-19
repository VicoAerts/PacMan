/**
 * @file Game.h
 * @brief Top-level game class that owns the render window and runs the main loop.
 */

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H

#include "../model/Score.h"
#include "../states/StateManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

namespace view {
/**
 * @brief Manages the main game loop and delegates logic to the active State.
 *
 * Creates the SFML window, initializes the StateManager, and forwards input,
 * update ticks, and rendering to the current state.
 */
class Game {
    /**
     * game window using sfml
     */
    std::shared_ptr<sf::RenderWindow> window;

    /** @brief State stack/controller handling state transitions. */
    std::unique_ptr<state::StateManager> stateManager;

    /** score of the player */
    std::shared_ptr<model::Score> playerScore;

public:
    /**Constructs the game and initializes window and initial state. */
    Game();

    /** destructor of the game*/
    ~Game();

    /** runs the main game loop */
    void run();

    /** close the game window */
    void close();

    /** handle events */
    void handleEvents();

    /** render the game */
    void render();

    /** update the game  */
    void update(double deltaTime);
};
} // namespace view
#endif // PACMAN_GAME_H
