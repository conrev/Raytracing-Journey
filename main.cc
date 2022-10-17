#include "core/camera.h"
#include "core/renderer.h"
#include "objects/sphere.h"
#include "objects/plane.h"
#include "material/lambertian.h"
#include "material/metal.h"

#include "app.h"

std::vector<std::shared_ptr<hittable>> create_random_scene()
{
    std::vector<std::shared_ptr<hittable>>
        objects;

    std::shared_ptr<lambertian> diffusered = std::make_shared<lambertian>(glm::vec3(0.7, 0.3, 0.3));
    std::shared_ptr<lambertian> diffusewhite = std::make_shared<lambertian>(glm::vec3(0.8, 0.8, 0.8));
    std::shared_ptr<metal> metalblue = std::make_shared<metal>(glm::vec3(0.8, 0.8, 0.8), 1.0f);

    objects.push_back(std::make_shared<sphere>(sphere{glm::vec3(0.0, 0.0, -1.0f), 0.5f, diffusered}));
    objects.push_back(std::make_shared<sphere>(sphere{glm::vec3(1.0f, 0.0, -1.0f), 0.4f, metalblue}));
    //   objects.push_back(sphere{vec3(-1.0f, 1.0, -1.7f), 0.3f});
    objects.push_back(std::make_shared<plane>(plane{glm::vec3{0.0, -0.5f, -0.0f}, glm::vec3{0.0, 1.0, 0.0}, diffusewhite}));

    return objects;
}

int main()
{
    std::string app_title = "Raytracing Journey";
    app *running_app = new app(app_title, 800, 600);
    running_app->run();
    return 0;
}
