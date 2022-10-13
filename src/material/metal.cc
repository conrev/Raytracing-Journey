#include "material/metal.h"
#include "hittable.h"

bool metal::scatter(const ray &ray_in, const hitdata &rec, color &attenuation, ray &scattered_ray) const
{

    scattered_ray = ray(rec.hit_position, reflect(ray_in.direction().normalize(), rec.normal) + m_fuzziness * random_inside_unit_sphere());
    attenuation = m_albedo;
    // if they have less than 90 degrees angle, then they continue scattering.
    // otherwise they should give out any color
    return dot(scattered_ray.direction(), rec.normal) > 0;
}