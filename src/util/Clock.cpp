

#include "Clock.h"

util::Clock& util::Clock::getInstance() {
    static Clock _instance{};
    return _instance;
}

void util::Clock::start() {
    time = std::chrono::steady_clock::now();
    deltaTime = 0.0;
}
void util::Clock::tick() {
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = now - time;
    deltaTime = diff.count();
    time = now;
}

double util::Clock::getDeltaTime() { return deltaTime; }