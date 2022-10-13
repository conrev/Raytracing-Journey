#include "common.h"
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "objects/sphere.h"
#include "material/lambertian.h"
#include "material/metal.h"
#include "camera.h"
#include "objects/plane.h"

color ray_color(std ::vector<std::shared_ptr<hittable>> &objects, const ray &r, int recurse_depth)
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
            return current_color * ray_color(objects, scattered_ray, recurse_depth - 1);
        // object doesnt scatter any light
        return color(0.0, 0.0, 0.0);
    }
    vec3 unit_direction = r.direction().normalize();
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{

    camera cam(point3(0, 0, 0), point3(0, 0, 0), 130, 16.0 / 9.0);
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / cam.aspect_ratio());

    // Render
    std::vector<std::shared_ptr<hittable>>
        objects;

    std::shared_ptr<lambertian> diffusered = std::make_shared<lambertian>(color(0.7, 0.3, 0.3));
    std::shared_ptr<lambertian> diffusewhite = std::make_shared<lambertian>(color(0.8, 0.8, 0.8));
    std::shared_ptr<metal> metalblue = std::make_shared<metal>(color(0.8, 0.8, 0.8), 1.0f);
    objects.push_back(std::make_shared<sphere>(sphere{vec3(0.0, 0.0, -1.0f), 0.5f, diffusered}));
    objects.push_back(std::make_shared<sphere>(sphere{vec3(1.0f, 0.0, -1.0f), 0.4f, metalblue}));
    //   objects.push_back(sphere{vec3(-1.0f, 1.0, -1.7f), 0.3f});
    objects.push_back(std::make_shared<plane>(plane{point3{0.0, -0.5f, -0.0f}, vec3{0.0, 1.0, 0.0}, diffusewhite}));

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