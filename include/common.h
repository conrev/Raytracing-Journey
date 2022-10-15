#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <memory>

namespace constants
{
    const double INF = std::numeric_limits<double>::infinity();
    const double PI = 3.1415926535897932385;
    const double SAMPLES_PER_PIXEL = 100;
    const int RAY_RECURSIVE_DEPTH = 50;
    const int IMAGE_WIDTH = 400;

}

inline double random_double()
{
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
    return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

inline double degrees_to_radians(double deg)
{
    return deg / 180.0f * constants::PI;
}

#endif