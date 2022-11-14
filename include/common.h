#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <memory>

namespace constants
{
    const float INF = std::numeric_limits<float>::infinity();
    const float PI = 3.1415926535897932385;
}

namespace settings
{
    extern int SAMPLES_PER_PIXEL;
    extern int RAY_RECURSIVE_DEPTH;
}

inline float random_float()
{
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline float random_float(float min, float max)
{
    return min + (max - min) * random_float();
}

inline float clamp(float x, float min, float max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

inline float degrees_to_radians(double deg)
{
    return deg / 180.0f * constants::PI;
}

#endif