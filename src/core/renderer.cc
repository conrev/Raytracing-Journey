#include "core/renderer.h"

namespace util
{
    void write_color(std::ostream &out, color pixel_color)
    {
        double r = sqrt(pixel_color.x());
        double g = sqrt(pixel_color.y());
        double b = sqrt(pixel_color.z());

        // Write the translated [0,255] value of each color component.
        out << static_cast<int>(255.999 * clamp(r, 0.0f, 0.999f)) << ' '
            << static_cast<int>(255.999 * clamp(g, 0.0f, 0.999f)) << ' '
            << static_cast<int>(255.999 * clamp(b, 0.0f, 0.999f)) << '\n';
    }

    void write_to_stdout(const std::vector<color> &buffer, int image_height, int image_width)
    {
        std::cout
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

}

color renderer::per_pixel(double u, double v) const
{
    ray cur_ray = m_camera.generate_ray(u, v);
    color current_color = vec3(1.0, 1.0, 1.0);
    for (int i = 0; i < constants::RAY_RECURSIVE_DEPTH; i++)
    {
        hitdata hit;
        double min_t = constants::INF;
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
            color scattered_color;
            ray scattered_ray;
            if (hit.hit_material->scatter(cur_ray, hit, scattered_color, scattered_ray))
            {
                current_color *= scattered_color;
                cur_ray = scattered_ray;
            }
            else
            {
                // object doesnt scatter any light
                return color(0.0, 0.0, 0.0);
            }
        }
        else
        {
            vec3 unit_direction = cur_ray.direction().normalize();
            double t = 0.5 * (unit_direction.y() + 1.0);
            color bg = (1.0f - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
            return current_color * bg;
        }
    }
    // out of recursive depth
    return color(0.0, 0.0, 0.0);
}

color renderer::per_pixel(const ray &r, int recurse_depth) const
{
    hitdata hit;
    double min_t = constants::INF;
    bool hit_anything = false;

    if (recurse_depth <= 0)
    {
        return color(0.0, 0.0, 0.0);
    }

    for (const auto &obj : m_objects)
    {
        hitdata temp;
        bool intersect = obj->hit(r, 0.001f, min_t, temp);
        if (intersect)
        {
            hit_anything = true;
            hit = temp;
            min_t = temp.t;
        }
    }
    if (hit_anything)
    {
        color current_color;
        ray scattered_ray;
        if (hit.hit_material->scatter(r, hit, current_color, scattered_ray))
            return current_color * per_pixel(scattered_ray, recurse_depth - 1);
        // object doesnt scatter any light
        return color(0.0, 0.0, 0.0);
    }
    vec3 unit_direction = r.direction().normalize();
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

void renderer::render()
{
    for (int j = m_image_height - 1; j >= 0; --j)
    {
        for (int i = 0; i < m_image_width; ++i)
        {
            color final_color(0.0, 0.0, 0.0f);
            for (int s = 0; s < constants::SAMPLES_PER_PIXEL; ++s)
            {
                auto u = double(i + random_double()) / (m_image_width - 1); // normalized pixel coordinates
                auto v = double(j + random_double()) / (m_image_height - 1);
                // shoot from originto "canvas/viewport" coordinate
                // ray r = m_camera.generate_ray(u, v);
                final_color += per_pixel(u, v);
                // final_color += per_pixel(r, constants::RAY_RECURSIVE_DEPTH);
            }
            m_image_data[j * m_image_width + i] = final_color / constants::SAMPLES_PER_PIXEL;
        }
    }

    util::write_to_stdout(m_image_data, m_image_height, m_image_width);
}