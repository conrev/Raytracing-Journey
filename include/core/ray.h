#ifndef RAY_H
#define RAY_H

#include "glm/glm.hpp"

class ray
{
public:
    ray() = default;
    ray(const glm::vec3 &origin, const glm::vec3 &direction) : m_origin(origin), m_direction(direction)
    {
    }

    glm::vec3 eval(float t) const
    {
        return m_origin + (m_direction * t);
    }

    glm::vec3 origin() const { return m_origin; }
    glm::vec3 direction() const { return m_direction; }

private:
    glm::vec3 m_origin;
    glm::vec3 m_direction;
};

#endif