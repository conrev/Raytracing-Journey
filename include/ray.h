#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray
{
public:
    ray() = default;
    ray(const point3 &origin, const vec3 &direction) : m_origin(origin), m_direction(direction)
    {
    }

    point3 eval(double t) const
    {
        return m_origin + (m_direction * t);
    }

    point3 origin() const { return m_origin; }
    vec3 direction() const { return m_direction; }

private:
    point3 m_origin;
    vec3 m_direction;
};

#endif