

#include "Clock.h"
model::Clock* model::Clock::_instance = nullptr;

model::Clock* model::Clock::getInstance() {
    if (!_instance)
        _instance = new Clock();
    return _instance;
}

void model::Clock::start() { time = std::chrono::steady_clock::now(); }

double model::Clock::getDeltaTime() {
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = now - time;
    time = now;
    return diff.count();
}