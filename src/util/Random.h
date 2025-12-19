/**
 *@file Random.h
 *@brief Declaration of the Random class. Utility for generating random numbers.
 *
 */
#ifndef PACMAN_RANDOM_H
#define PACMAN_RANDOM_H
#include <random>

namespace util {
/**
 * @brief Pseudo-random number generator wrapper.
 *
 * Uses a Mersenne Twister engine seeded with std::random_device.
 * Intended for general-purpose randomness within the game logic.
 */
class Random {
public:
    /** Constructor that seeds the random number generator */
    Random() : rng(std::random_device{}()) {}
    /** Generate a random integer in the range [min, max] */
    int randomInt(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

private:
    /** Mersenne Twister random number generator */
    std::mt19937 rng;
};
} // namespace util

#endif // PACMAN_RANDOM_H
