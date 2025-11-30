//
// Created by gebruiker on 30/11/2025.
//

#include "Score.h"
void model::Score::onNotify(const events::Event& event, Entity& entity) {
    switch (event.type) {
    case events::EventType::CoinEaten:
        handleCoinCollected();
        break;
    default:
        break;
    }
}
void model::Score::handleCoinCollected() {
    float elapsedTime = model::Clock::getInstance()->getDeltaTime();
    timeSinceLastCoin += elapsedTime;

    // calculate bonus based on time since last coin collected
    int baseScore = 10;
    int bonus = 0;
    // window for bonus decreases over 3 seconds
    float bonusWindow = 3.f;
    if (timeSinceLastCoin < bonusWindow) {
        bonus = (bonusWindow - timeSinceLastCoin) * 5;
    }
    m_score += baseScore + bonus;
    timeSinceLastCoin = 0.f;
}
void model::Score::update(float deltaTime) {
    timeSinceLastCoin += deltaTime;
    m_score -= deltaTime; // decrease score over time with 1 point per second
    if (m_score < 0) {
        m_score = 0;
    }
}
void model::Score::saveToFile() {}