/**
 *@file Random.h
 *@brief Declaration of the Random class.
 *
 */
#ifndef PACMAN_RANDOM_H
#define PACMAN_RANDOM_H
#include <random>

namespace util {
class Random {
public:
    Random() : rng(std::random_device{}()) {}
    /** Generate a random integer in the range [min, max] */
    int randomInt(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

private:
    std::mt19937 rng;
};
} // namespace util

#endif // PACMAN_RANDOM_H
