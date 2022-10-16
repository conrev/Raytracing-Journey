#include "common.h"
#include "ray.h"
#include "camera.h"
#include "objects/sphere.h"
#include "material/lambertian.h"
#include "material/metal.h"
#include "objects/plane.h"
#include "core/renderer.h"
#include "glm/glm.hpp"

int main()
{

    camera cam(glm::vec3(0.0f), glm::vec3(0.0f), 130, 16.0 / 9.0);
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / cam.aspect_ratio());

    // Render
    std::vector<std::shared_ptr<hittable>>
        objects;

    std::shared_ptr<lambertian> diffusered = std::make_shared<lambertian>(glm::vec3(0.7, 0.3, 0.3));
    std::shared_ptr<lambertian> diffusewhite = std::make_shared<lambertian>(glm::vec3(0.8, 0.8, 0.8));
    std::shared_ptr<metal> metalblue = std::make_shared<metal>(glm::vec3(0.8, 0.8, 0.8), 1.0f);
    objects.push_back(std::make_shared<sphere>(sphere{glm::vec3(0.0, 0.0, -1.0f), 0.5f, diffusered}));
    objects.push_back(std::make_shared<sphere>(sphere{glm::vec3(1.0f, 0.0, -1.0f), 0.4f, metalblue}));
    //   objects.push_back(sphere{vec3(-1.0f, 1.0, -1.7f), 0.3f});
    objects.push_back(std::make_shared<plane>(plane{glm::vec3{0.0, -0.5f, -0.0f}, glm::vec3{0.0, 1.0, 0.0}, diffusewhite}));

    std::unique_ptr<renderer> renderer_ptr = std::make_unique<renderer>(cam, objects, image_width);
    renderer_ptr->render();
}