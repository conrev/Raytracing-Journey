#ifndef HITTABLE_H
#define HITTABLE_H

#include "glm/glm.hpp"
#include "common.h"
#include "ray.h"

class material;

struct hitdata
{
    glm::vec3 hit_position;
    glm::vec3 normal;
    float t;
    std::shared_ptr<material> hit_material;

    bool front_face;

    inline void set_face_normal(const ray &source, const glm::vec3 &outward_normal)
    {
        // if their angle is less than 90, they face the same direction
        // meaning that the contact is inside the surface
        // per convention, normal is reverse direction from the ray
        if (glm::dot(source.direction(), outward_normal) > 0.0f)
        {
            front_face = false;
            normal = -outward_normal;
        }
        else
        {
            front_face = true;
            normal = outward_normal;
        }
    }
};

class hittable
{
public:
    hittable() = default;
    virtual bool hit(const ray &raySource, float t_min, float t_max, hitdata &hitInfo) const = 0;
};

#endif