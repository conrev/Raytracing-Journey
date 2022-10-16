#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "common.h"
#include "ray.h"

class camera
{
public:
    camera(const glm::vec3 &lookfrom, const glm::vec3 &lookat, float vfov, float aspect_ratio) : m_aspect_ratio(aspect_ratio)
    {
        // Image
        float theta = degrees_to_radians(vfov);
        float h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = m_aspect_ratio * viewport_height;
        auto focal_length = 1.0;

        m_origin = glm::vec3(0, 0, 0);
        m_horizontal_span = glm::vec3(viewport_width, 0, 0);
        m_vertical_span = glm::vec3(0, viewport_height, 0);
        m_lower_left_corner = m_origin - m_horizontal_span / 2.0f - m_vertical_span / 2.0f - glm::vec3(0, 0, focal_length);
    }

    ray generate_ray(float u, float v) const
    {
        return ray(m_origin, m_lower_left_corner + (u * m_horizontal_span) + (v * m_vertical_span) - m_origin);
    }

    float aspect_ratio() const
    {
        return m_aspect_ratio;
    }

private:
    float m_aspect_ratio;
    glm::vec3 m_origin;
    // size of the viewport horizontally
    glm::vec3 m_horizontal_span;
    // size of the viewport vertically
    glm::vec3 m_vertical_span;
    // 3D position of lower level corner of the viewport
    glm::vec3 m_lower_left_corner;
};

#endif