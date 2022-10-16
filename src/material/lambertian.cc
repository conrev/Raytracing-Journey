#include "material/lambertian.h"
#include "glm/gtc/random.hpp"
#include "glm/gtc/epsilon.hpp"

bool lambertian::scatter(const ray &ray_in, const hitdata &rec, glm::vec3 &attenuation, ray &scattered_ray) const
{
    glm::vec3 diffuse_target = rec.normal + glm::normalize(glm::ballRand(1.0f));

    float epsilon = 1e-8;

    if (glm::all(glm::epsilonEqual(diffuse_target, glm::vec3(0.0f, 0.0f, 0.0f), epsilon)))
        diffuse_target = rec.normal;

    scattered_ray = ray(rec.hit_position, diffuse_target);

    attenuation = m_albedo;
    return true;
}