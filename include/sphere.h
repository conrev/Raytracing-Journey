#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
public:
    sphere() = default;
    sphere(point3 center, double radius) : m_center(center), m_radius(radius){};
    virtual bool hit(const ray &raySource, double t_min, double t_max, hitdata &hitInfo) const override;

private:
    double m_radius;
    point3 m_center;
};

#endif