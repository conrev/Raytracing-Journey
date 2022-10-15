#ifndef RENDERER_H
#define RENDERER_H

#include "common.h"
#include "hittable.h"
#include "camera.h"
#include "material/material.h"

class renderer
{
public:
    renderer(const camera &camera, const std::vector<std::shared_ptr<hittable>> &objects, int image_width) : m_camera(camera), m_objects(objects), m_image_width(image_width)
    {
        m_image_height = static_cast<int>(image_width / m_camera.aspect_ratio());
        m_image_data.reserve(m_image_height * m_image_width);
    }

public:
    color per_pixel(double u, double v) const;
    color per_pixel(const ray &r, int recurse_depth) const;
    void render();

private:
    int m_image_width;
    int m_image_height;
    camera m_camera;
    std::vector<std::shared_ptr<hittable>> m_objects;
    std::vector<color> m_image_data;
};

#endif