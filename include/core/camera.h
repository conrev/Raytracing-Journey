#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/random.hpp"
#include "core/ray.h"
#include "common.h"

class camera
{
public:
    camera(const glm::vec3 &lookfrom, const glm::vec3 &lookat, const glm::vec3 &up, float vfov, float aspect_ratio, float aperture, float focus_distance) : m_aperture(aperture), m_aspect_ratio(aspect_ratio)
    {
        // Image
        float theta = degrees_to_radians(vfov);
        float h = tan(theta / 2);
        float viewport_height = 2.0 * h;
        float viewport_width = m_aspect_ratio * viewport_height;

        m_origin = lookfrom;
        glm::vec3 distance_vec = glm::normalize(lookfrom - lookat);

        m_horizontal_camera_basis = glm::normalize(glm::cross(distance_vec, up));
        m_vertical_camera_basis = glm::normalize(glm::cross(m_horizontal_camera_basis, distance_vec));

        m_horizontal_span = viewport_width * m_horizontal_camera_basis;
        m_vertical_span = viewport_height * m_vertical_camera_basis;
        m_lower_left_corner = m_origin - m_horizontal_span / 2.0f - m_vertical_span / 2.0f - distance_vec * focus_distance;
    }

    ray generate_ray(float u, float v) const
    {
        glm::vec3 offset = m_aperture / 2.0f * glm::vec3(glm::diskRand(1.0f), 0.0f);
        glm::vec3 camera_space_offset = m_horizontal_camera_basis * offset.x + m_vertical_camera_basis * offset.y;
        return ray(m_origin + camera_space_offset, m_lower_left_corner + (u * m_horizontal_span) + (v * m_vertical_span) - m_origin - camera_space_offset);
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
    glm::vec3 m_horizontal_camera_basis;
    glm::vec3 m_vertical_camera_basis;
    float m_aperture;
};

#endif