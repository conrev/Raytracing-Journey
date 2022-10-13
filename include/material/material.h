#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "vec3.h"

struct hitdata;

class material
{
public:
    material() = default;
    virtual bool scatter(const ray &ray_in, const hitdata &rec, color &attenuation, ray &scattered_ray) const = 0;
};

#endif