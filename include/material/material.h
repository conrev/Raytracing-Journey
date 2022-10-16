#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "glm/glm.hpp"

struct hitdata;

class material
{
public:
    material() = default;
    virtual bool scatter(const ray &ray_in, const hitdata &rec, glm::vec3 &attenuation, ray &scattered_ray) const = 0;
};

#endif