

#include "Clock.h"
logic::Clock* logic::Clock::_instance = nullptr;

logic::Clock* logic::Clock::getInstance() {
    if (!_instance)
        _instance = new Clock();
    return _instance;
}

void logic::Clock::start() { time = std::chrono::steady_clock::now(); }

double logic::Clock::getDeltaTime() {
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = now - time;
    time = now;
    return diff.count();
}