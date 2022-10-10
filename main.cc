#include "common.h"
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "camera.h"

color ray_color(std ::vector<sphere> &objects, const ray &r, int recurse_depth)
{
    hitdata hit;
    double min_t = constants::inf;
    bool hit_anything = false;

    if (recurse_depth <= 0)
    {
        return color(0.0, 0.0, 0.0);
    }

    for (const auto &obj : objects)
    {
        hitdata temp;
        bool intersect = obj.hit(r, 0.001f, min_t, temp);
        if (intersect)
        {
            hit_anything = true;
            hit = temp;
            min_t = temp.t;
        }
    }
    if (hit_anything)
    {
        point3 diffuse_target = hit.hit_position + hit.normal + random_inside_unit_sphere().normalize();
        return 0.5 * ray_color(objects, ray(hit.hit_position, diffuse_target - hit.hit_position), recurse_depth - 1);
    }
    vec3 unit_direction = r.direction().normalize();
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{

    camera cam;
    const double aspect_ratio = 16.0f / 9.0f;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Render
    std::vector<sphere>
        objects;
    objects.push_back(sphere{vec3(0.0, 0.0, -1.0f), 0.5f});
    objects.push_back(sphere{vec3(0.0, -100.5, -1.0f), 100.0f});

    std::cout
        << "P3\n"
        << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            color final_color(0.0, 0.0, 0.0f);
            for (int s = 0; s < constants::samples_per_pixel; ++s)
            {
                auto u = double(i + random_double()) / (image_width - 1); // normalized pixel coordinates
                auto v = double(j + random_double()) / (image_height - 1);
                // shoot from originto "canvas/viewport" coordinate
                ray r = cam.generate_ray(u, v);
                final_color += ray_color(objects, r, constants::ray_recursive_depth);
            }
            write_color(std::cout, final_color, constants::samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}