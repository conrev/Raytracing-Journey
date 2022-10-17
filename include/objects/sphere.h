#ifndef SPHERE_H
#define SPHERE_H

#include "glm/glm.hpp"

#include "core/hittable.h"

class sphere : public hittable
{
public:
    sphere() = default;
    sphere(const glm::vec3 &center, float radius, std::shared_ptr<material> material) : m_center(center), m_radius(radius), m_material(material){};
    virtual bool hit(const ray &raySource, float t_min, float t_max, hitdata &hitInfo) const override;

private:
    float m_radius;
    glm::vec3 m_center;
    std::shared_ptr<material> m_material;
};

#endif