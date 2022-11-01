#include "core/renderer.h"

namespace util
{
    void write_color(std::ostream &out, glm::vec3 pixel_color)
    {
        float r = sqrt(pixel_color.x);
        float g = sqrt(pixel_color.y);
        float b = sqrt(pixel_color.z);

        // Write the translated [0,255] value of each color component.
        out << static_cast<int>(255.999 * clamp(r, 0.0f, 0.999f)) << ' '
            << static_cast<int>(255.999 * clamp(g, 0.0f, 0.999f)) << ' '
            << static_cast<int>(255.999 * clamp(b, 0.0f, 0.999f)) << '\n';
    }

    void write_image(std::ostream &out, const std::vector<glm::vec3> &buffer, int image_height, int image_width)
    {
        out
            << "P3\n"
            << image_width << " " << image_height << "\n255\n";

        for (int j = image_height - 1; j >= 0; --j)
        {
            for (int i = 0; i < image_width; ++i)
            {
                util::write_color(std::cout, buffer[j * image_width + i]);
            }
        }
    }

    void write_progress(std::ostream &out, int current_scanline, int full_scanline)
    {
        float progress = static_cast<float>(full_scanline - current_scanline) / full_scanline * 100;
        out << "\rRendering : " << progress << "% " << std::flush;
    }

}

glm::vec3 renderer::per_pixel(ray cur_ray) const
{

    glm::vec3 current_color = glm::vec3(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < constants::RAY_RECURSIVE_DEPTH; i++)
    {
        hitdata hit;
        float min_t = constants::INF;
        bool hit_anything = false;

        for (const auto &obj : m_objects)
        {
            hitdata temp;
            bool intersect = obj->hit(cur_ray, 0.001f, min_t, temp);
            if (intersect)
            {
                hit_anything = true;
                hit = temp;
                min_t = temp.t;
            }
        }
        if (hit_anything)
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

void renderer::render()
{
#pragma omp parallel for
    for (int j = 0; j < m_image_height; ++j)
    {
        // util::write_progress(std::cerr, j, m_image_height);
        for (int i = 0; i < m_image_width; ++i)
        {
            glm::vec3 final_color(0.0f);
            for (int s = 0; s < constants::SAMPLES_PER_PIXEL; ++s)
            {
                auto u = float(i + random_float()) / (m_image_width - 1); // normalized pixel coordinates
                auto v = float(j + random_float()) / (m_image_height - 1);
                // shoot from originto "canvas/viewport" coordinate
                ray r = m_camera.generate_ray(u, v);
                final_color += per_pixel(r);
                // final_color += per_pixel(r, constants::RAY_RECURSIVE_DEPTH);
            }
            m_image_data[(m_image_height - 1 - j) * m_image_width + i] = glm::sqrt(final_color / constants::SAMPLES_PER_PIXEL);
        }
    }
    // util::write_image(std::cout, m_image_data, m_image_height, m_image_width);
}

void renderer::on_resize(int new_width, int new_height)
{
    m_camera.on_resize(static_cast<float>(new_width) / new_height);
    m_image_data.resize(new_width * new_height);
    m_image_height = new_height;
    m_image_width = new_width;
}