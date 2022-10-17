#include "glm/gtc/random.hpp"

#include "material/metal.h"

bool metal::scatter(const ray &ray_in, const hitdata &rec, glm::vec3 &attenuation, ray &scattered_ray) const
{

    scattered_ray = ray(rec.hit_position, glm::reflect(glm::normalize(ray_in.direction()), rec.normal) + m_fuzziness * glm::ballRand(1.0f));
    attenuation = m_albedo;
    // if they have less than 90 degrees angle, then they continue scattering.
    // otherwise they should give out any color
    return dot(scattered_ray.direction(), rec.normal) > 0;
}