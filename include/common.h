#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
#include <limits>

#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"

namespace constants
{
    const double inf = std::numeric_limits<double>::infinity();
    const double pi = 3.1415926535897932385;
}

#endif