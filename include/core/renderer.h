#ifndef RENDERER_H
#define RENDERER_H

#include "material/lambertian.h"
#include "material/metal.h"
#include "material/dielectric.h"
#include "core/camera.h"
#include "core/scene.h"
#include "objects/group.h"
#include "objects/sphere.h"
#include "objects/plane.h"
#include "common.h"

class renderer
{
public:
    renderer(int image_width, int image_height) : m_image_height(image_height), m_image_width(image_width)
    {
        m_image_data.reserve(m_image_height * m_image_width);
    }

public:
    glm::vec3 per_pixel(ray cur_ray, const std::shared_ptr<group> &objects_to_render) const;
    glm::vec3 *get_image_data() { return m_image_data.data(); };
    void render(const scene &active_scene, int active_camera_id);
    void on_resize(int new_width, int new_height);

private:
    int m_image_width;
    int m_image_height;
    std::vector<glm::vec3> m_image_data;
};

#endif