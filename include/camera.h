#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"
#include "vec3.h"
#include "ray.h"

class camera
{
public:
    camera(point3 lookfrom, point3 lookat, double vfov, double aspect_ratio) : m_aspect_ratio(aspect_ratio)
    {
        // Image
        double theta = degrees_to_radians(vfov);
        double h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = m_aspect_ratio * viewport_height;
        auto focal_length = 1.0;

        m_origin = point3(0, 0, 0);
        m_horizontal_span = vec3(viewport_width, 0, 0);
        m_vertical_span = vec3(0, viewport_height, 0);
        m_lower_left_corner = m_origin - m_horizontal_span / 2 - m_vertical_span / 2 - vec3(0, 0, focal_length);
    }

    ray generate_ray(double u, double v)
    {
        return ray(m_origin, m_lower_left_corner + (u * m_horizontal_span) + (v * m_vertical_span) - m_origin);
    }

    double aspect_ratio() const
    {
        return m_aspect_ratio;
    }

private:
    double m_aspect_ratio;
    point3 m_origin;
    // size of the viewport horizontally
    vec3 m_horizontal_span;
    // size of the viewport vertically
    vec3 m_vertical_span;
    // 3D position of lower level corner of the viewport
    vec3 m_lower_left_corner;
};

#endif