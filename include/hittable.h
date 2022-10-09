#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"
#include "ray.h"

struct hitdata
{
    point3 hit_position;
    vec3 normal;
    double t;
};

class hittable
{
public:
    hittable() = default;
    virtual bool hit(const ray &raySource, double t_min, double t_max, hitdata &hitInfo) const = 0;
};

#endif