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

public:
    /** when event occurs , update score accordingly */
    void onNotify(const events::Event& event, Entity& entity) override;
    /** get current score */
    [[nodiscard]] int getScore() const { return m_score; }
    /** handle coin collected event */
    void handleCoinCollected();
    /** update every frame to track time since last coin */
    void update(float deltaTime);
    /** save score to file */
    void saveToFile();
};
} // namespace model

#endif // PACMAN_SCORE_H
