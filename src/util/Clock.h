/**
 * @file Clock.h
 * @brief Singleton Clock class to manage time tracking.
 *
 */

#ifndef PACMAN_CLOCK_H
#define PACMAN_CLOCK_H
#include <chrono>
namespace util {
class Clock {
private:
    static Clock* _instance;

    Clock() = default;

    std::chrono::time_point<std::chrono::steady_clock> time;

    double deltaTime = 0.0;

public:
    ~Clock() = default;

    static Clock* getInstance();

    void start();

    void tick();

    double getDeltaTime();

    Clock(const Clock&) = delete;

    Clock& operator=(const Clock&) = delete;
};
} // namespace util
#endif // PACMAN_CLOCK_H
