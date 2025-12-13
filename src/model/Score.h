/**
 * @file Score.h
 * @brief score is an observer that tracks the score of the player
 */

#ifndef PACMAN_SCORE_H
#define PACMAN_SCORE_H
#include "../util/Clock.h"
#include "Observer.h"

namespace model {
class Score : public Observer {
private:
    int m_score = 0;
    float timeSinceLastCoin = 0.f;
    int lives = 3;
    bool gameOver = false;

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
    /** update every frame to track time since last coin */
    void update(float deltaTime);
    /** save score to file */
    void saveToFile();
    /** check if game is over */
    [[nodiscard]] bool isGameOver() const;
};
} // namespace model

#endif // PACMAN_SCORE_H
