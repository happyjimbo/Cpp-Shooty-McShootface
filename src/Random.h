#ifndef CMAKESFMLPROJECT_RANDOM_H
#define CMAKESFMLPROJECT_RANDOM_H


#include <random>

// Utility function to generate a random float within a range
inline float getRandomFloat(float min, float max) {
    static std::random_device rd;    // Random number generator
    static std::mt19937 gen(rd());   // Mersenne Twister engine
    std::uniform_real_distribution<> dis(min, max);
    return static_cast<float>(dis(gen));
};

#endif // CMAKESFMLPROJECT_RANDOM_H