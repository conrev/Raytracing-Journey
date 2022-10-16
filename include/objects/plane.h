#ifndef PLANE_H
#define PLANE_H

#include "hittable.h"

class plane : public hittable
{

public:
    plane() = default;
    plane(const glm::vec3 &point, const glm::vec3 &normal, std::shared_ptr<material> material) : m_point_in_plane(point), m_normal(normal), m_material(material) {}
    virtual bool hit(const ray &raySource, float t_min, float t_max, hitdata &hitInfo) const override;

private:
    glm::vec3 m_point_in_plane;
    glm::vec3 m_normal;
    std::shared_ptr<material> m_material;
};

#endif