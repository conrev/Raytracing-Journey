#ifndef PLANE_H
#define PLANE_H

#include "hittable.h"

class plane : public hittable
{

public:
    plane() = default;
    plane(const point3 &point, const vec3 &normal, std::shared_ptr<material> material) : m_point_in_plane(point), m_normal(normal), m_material(material) {}
    virtual bool hit(const ray &raySource, double t_min, double t_max, hitdata &hitInfo) const override;

private:
    point3 m_point_in_plane;
    vec3 m_normal;
    std::shared_ptr<material> m_material;
};

#endif