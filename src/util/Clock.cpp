

#include "Clock.h"
util::Clock* util::Clock::_instance = nullptr;

util::Clock* util::Clock::getInstance() {
    if (!_instance)
        _instance = new Clock();
    return _instance;
}

void util::Clock::start() { time = std::chrono::steady_clock::now(); }

double util::Clock::getDeltaTime() {
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = now - time;
    time = now;
    return diff.count();
}