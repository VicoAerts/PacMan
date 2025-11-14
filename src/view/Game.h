/**
 *@file Game.h
 *@brief creates renderwindow, starts the game loop, sets up stateManager , passes events to stateManager,
 */

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H

#include "../states/StateManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
namespace logic {
class World;
}

namespace view {
class Game {
    /**
     * game window using sfml
     */
    std::shared_ptr<sf::RenderWindow> window;
    /**
     * game world using logic world world class will handle all game logic
     */

    std::unique_ptr<logic::World> world;

    // state manager, elke state heeft pointer naar deze statemanager
    std::unique_ptr<state::StateManager> stateManager;

public:
    /**
     * constructor
     * sets up the game window and world ....
     */
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
