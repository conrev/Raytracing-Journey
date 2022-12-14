#include "core/renderer.h"

glm::vec3 renderer::per_pixel(ray cur_ray, const std::shared_ptr<group> &objects_to_render) const
{

    glm::vec3 current_color = glm::vec3(1.0f, 1.0f, 1.0f);
    for (size_t i = 0; i < settings::RAY_RECURSIVE_DEPTH; i++)
    {
        hitdata hit;

        if (objects_to_render->hit(cur_ray, 0.001, constants::INF, hit))
        {
            glm::vec3 scattered_color;
            ray scattered_ray;
            if (hit.hit_material->scatter(cur_ray, hit, scattered_color, scattered_ray))
            {
                current_color *= scattered_color;
                cur_ray = scattered_ray;
            }
            else
            {
                // object doesnt scatter any light
                return glm::vec3(0.0f);
            }
        }
        else
        {
            glm::vec3 unit_direction = glm::normalize(cur_ray.direction());
            float t = 0.5 * (unit_direction.y + 1.0);
            glm::vec3 bg = (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
            return current_color * bg;
        }
    }
    // out of recursive depth
    return glm::vec3(0.0f);
}

void renderer::render(const scene &scene_to_render, int active_camera_id)
{

    camera active_cam = scene_to_render.cameras[active_camera_id];
    active_cam.on_resize(static_cast<float>(m_image_width) / m_image_height);

#pragma omp parallel for
    for (size_t j = 0; j < m_image_height; ++j)
    {
        // util::write_progress(std::cerr, j, m_image_height);
        for (size_t i = 0; i < m_image_width; ++i)
        {
            glm::vec3 final_color(0.0f);
            for (size_t s = 0; s < settings::SAMPLES_PER_PIXEL; ++s)
            {
                auto u = float(i + random_float()) / (m_image_width - 1); // normalized pixel coordinates
                auto v = float(j + random_float()) / (m_image_height - 1);
                // shoot from originto "canvas/viewport" coordinate
                ray r = active_cam.generate_ray(u, v);
                final_color += per_pixel(r, scene_to_render.objects);
            }
            m_image_data[(m_image_height - 1 - j) * m_image_width + i] = glm::sqrt(final_color / static_cast<float>(settings::SAMPLES_PER_PIXEL));
        }
    }
    // util::write_image(std::cout, m_image_data, m_image_height, m_image_width);
}

void renderer::on_resize(int new_width, int new_height)
{
    if (new_width == m_image_width && new_height == m_image_height)
        return;

    m_image_data.resize(new_width * new_height);
    m_image_height = new_height;
    m_image_width = new_width;
}