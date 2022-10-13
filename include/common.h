#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <memory>

namespace constants
{
    const double inf = std::numeric_limits<double>::infinity();
    const double pi = 3.1415926535897932385;
    const double samples_per_pixel = 100;
    const int ray_recursive_depth = 50;
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
    return deg / 180.0f * constants::pi;
}

#endif