//
// Created by gebruiker on 30/11/2025.
//

#include "Score.h"

#include <iostream>
#include <ostream>
void model::Score::onNotify(const events::Event& event, Entity& entity) {
    switch (event.type) {
    case events::EventType::CoinEaten:
        handleCoinCollected();
        break;
    case events::EventType::PacManDied:
        hanldePacmanDead();
        break;
    case events::EventType::FruitEaten:
        handleFruitCollected();
        break;
    case events::EventType::GhostEaten:
        std::cout << "ghost eaten" << std::endl;
        handleGhostEaten();
        break;
    default:
        break;
    }
}
void model::Score::handleCoinCollected() {
    float elapsedTime = util::Clock::getInstance()->getDeltaTime();
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
void model::Score::hanldePacmanDead() {
    if (lives > 1) {
        lives -= 1;
    }
    // when pacman dead
    else {
        std::cout << "pacmanDead" << std::endl;
        gameOver = true;
        lives = 0;
    }
}
void model::Score::handleFruitCollected() {
    m_score += 50;
    // reset ghossts eaten counter
    amountOfGhostsEaten = 0;
}
void model::Score::update(float deltaTime) {
    timeSinceLastCoin += deltaTime;
    m_score -= deltaTime; // decrease score over time with 1 point per second
    if (m_score < 0) {
        m_score = 0;
    }
}
void model::Score::saveToFile() {
    std::string filename = "../config/HighScores.txt";
    // read existing scores
    std::vector<int> scores;
    {
        std::ifstream inFile(filename);
        int s;
        while (inFile >> s) {
            scores.push_back(s);
        }
    }

    // add current score
    scores.push_back(m_score);

    // sort high to low
    std::sort(scores.begin(), scores.end(), std::greater<int>());

    // keep only top 5 scores
    if (scores.size() > 5) {
        scores.resize(5);
    }

    // write back to file
    std::ofstream outFile(filename, std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open HighScores.txt for writing." << std::endl;
        return;
    }

    for (int s : scores) {
        outFile << s << '\n';
    }
}
bool model::Score::isGameOver() const { return gameOver; }
void model::Score::nextLevelSet() {
    // reset time since last coin for next level
    timeSinceLastCoin = 0.f;
    currentLevel++;
}
void model::Score::handleGhostEaten() {
    amountOfGhostsEaten++;
    int ghostScore = 200 * (1 << (amountOfGhostsEaten - 1)); // 200, 400, 800, 1600
    m_score += ghostScore;
}
void model::Score::reset() {
    m_score = 0;
    lives = 3;
    gameOver = false;
    timeSinceLastCoin = 0.f;
    amountOfGhostsEaten = 0;
    currentLevel = 1;
}
bool model::Score::isHighScore() const {
    std::string filename = "../config/HighScores.txt";

    int highScore = 0;
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Unable to open HighScores.txt for reading." << std::endl;
        return false;
    }
    int maxScore = 0;
    int s;
    while (inFile >> s) {
        if (s > maxScore) {
            maxScore = s;
        }
    }

    return m_score >= maxScore;
}