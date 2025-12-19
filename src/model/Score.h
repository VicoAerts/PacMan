/**
 * @file Score.h
 * @brief score is an observer that tracks the score of the player
 */

#ifndef PACMAN_SCORE_H
#define PACMAN_SCORE_H
#include "../util/Clock.h"
#include "Observer.h"
#include <algorithm>
#include <fstream>
#include <vector>

namespace model {
/**
 * @brief Observer that updates the game score based on received events.
 *
 * Listens to gameplay events such as collecting coins, fruits,
 * eating ghosts, and Pac-Man deaths.
 */
class Score : public Observer {
private:
    int m_score = 0;
    float timeSinceLastCoin = 0.f;
    int lives = 3;
    bool gameOver = false;
    int amountOfGhostsEaten = 0;
    int currentLevel = 1;

public:
    /** when event occurs , update score accordingly */
    void onNotify(const events::Event& event, Entity& entity) override;

    /** get current score */
    [[nodiscard]] int getScore() const { return m_score; }

    /** get the amount of lives*/
    [[nodiscard]] int getLives() const { return lives; }

    /** handle coin collected event */
    void handleCoinCollected();

    /**handle pacman getting eaten*/
    void hanldePacmanDead();

    /** handle fruit collected event */
    void handleFruitCollected();

    /** update every frame to track time since last coin and subtract 1 coin per second*/
    void update(float deltaTime);

    /** save score to file */
    void saveToFile();

    /** check if game is over */
    [[nodiscard]] bool isGameOver() const;

    /** next level set */
    void nextLevelSet();

    /**handle ghost eaten event*/
    void handleGhostEaten();

    /** get current level*/
    [[nodiscard]] int getCurrentLevel() const { return currentLevel; }
    /** reset score and lives */
    void reset();

    /** check if current score is a high score */
    [[nodiscard]] bool isHighScore() const;

    /** get high scores from file */
    [[nodiscard]] std::vector<int> getHighScores() const;
};
} // namespace model

#endif // PACMAN_SCORE_H
