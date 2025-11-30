/**
 * @file Clock.h
 * @brief Singleton Clock class to manage time tracking.
 *
 */

#ifndef PACMAN_CLOCK_H
#define PACMAN_CLOCK_H
#include <chrono>
namespace model {
class Clock {
private:
    static Clock* _instance;

    Clock() = default;

    std::chrono::time_point<std::chrono::steady_clock> time;

public:
    ~Clock() = default;

    static Clock* getInstance();

    void start();

    double getDeltaTime();

    Clock(const Clock&) = delete;

    Clock& operator=(const Clock&) = delete;
};
} // namespace util
#endif // PACMAN_CLOCK_H
