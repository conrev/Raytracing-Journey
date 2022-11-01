#ifndef RENDERER_H
#define RENDERER_H

#include "material/material.h"
#include "core/camera.h"
#include "core/hittable.h"
#include "common.h"

class renderer
{
public:
    renderer(const camera &camera, const std::vector<std::shared_ptr<hittable>> &objects, int image_width, int image_height) : m_camera(camera), m_image_height(image_height), m_objects(objects), m_image_width(image_width)
    {
        m_image_data.reserve(m_image_height * m_image_width);
    }

public:
    glm::vec3 per_pixel(ray cur_ray) const;
    glm::vec3 *get_image_data() { return m_image_data.data(); };
    void render();
    void on_resize(int new_width, int new_height);

private:
    int m_image_width;
    int m_image_height;
    camera m_camera;
    std::vector<std::shared_ptr<hittable>> m_objects;
    std::vector<glm::vec3> m_image_data;
};

#endif