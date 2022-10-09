#include "common.h"

color ray_color(std ::vector<sphere> &objects, const ray &r)
{
    hitdata hit;
    double min_t = constants::inf;
    bool hit_anything = false;

    for (const auto &obj : objects)
    {
        hitdata temp;
        bool intersect = obj.hit(r, 0.0f, min_t, temp);
        if (intersect)
        {
            hit_anything = true;
            hit = temp;
            min_t = temp.t;
        }
    }
    if (hit_anything)
    {
        return 0.5 * (hit.normal + color(1.0, 1.0, 1.0));
    }
    vec3 unit_direction = r.direction().normalize();
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    // size of the viewport horizontally
    auto horizontal = vec3(viewport_width, 0, 0);
    // size of the viewport vertically
    auto vertical = vec3(0, viewport_height, 0);
    // 3D position of lower level corner of the viewport
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    // Render
    std::vector<sphere> objects;
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
            auto u = double(i) / (image_width - 1); // normalized pixel coordinates
            auto v = double(j) / (image_height - 1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin); // shoot from originto "canvas/viewport" coordinate
            color pixel_color = ray_color(objects, r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}