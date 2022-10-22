#ifndef RENDERER_H
#define RENDERER_H

#include "material/material.h"
#include "core/camera.h"
#include "core/hittable.h"
#include "common.h"

class renderer
{
public:
    renderer(const camera &camera, const std::vector<std::shared_ptr<hittable>> &objects, int image_width) : m_camera(camera), m_objects(objects), m_image_width(image_width)
    {
        m_image_height = static_cast<int>(image_width / m_camera.aspect_ratio());
        m_image_data.reserve(m_image_height * m_image_width);
    }

public:
    glm::vec3 per_pixel(float u, float v) const;
    glm::vec3 per_pixel(const ray &r, int recurse_depth) const;
    void render();
    glm::vec3 *get_image_data() { return m_image_data.data(); };

private:
    int m_image_width;
    int m_image_height;
    camera m_camera;
    std::vector<std::shared_ptr<hittable>> m_objects;
    std::vector<glm::vec3> m_image_data;
};

#endif