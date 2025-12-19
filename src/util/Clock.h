/**
 * @file Clock.h
 * @brief Singleton Clock class to manage time tracking.
 *
 */

#ifndef PACMAN_CLOCK_H
#define PACMAN_CLOCK_H
#include <chrono>
/**
 * @namespace  util
 * @brief Contains utility classes and functions used across the project.
 * This namespace provides general-purpose tools that assist in various tasks,
 */
namespace util {
/** @brief Singleton clock providing delta time between update ticks. */
class Clock {
private:
    /** Private constructor for singleton pattern */
    Clock() = default;

    std::chrono::time_point<std::chrono::steady_clock> time;

    double deltaTime = 0.0;

public:
    /** Get the singleton instance of the Clock */
    static Clock& getInstance();
    /** Destructor */
    ~Clock() = default;
    /** Start the clock by recording the current time */
    void start();
    /** Update the clock and calculate delta time since last tick */
    void tick();
    /** Get the delta time since the last tick */
    [[nodiscard]] double getDeltaTime();
    /** Delete copy constructor and assignment operator to enforce singleton */
    Clock(const Clock&) = delete;
    Clock& operator=(const Clock&) = delete;
};
} // namespace util
#endif // PACMAN_CLOCK_H
