#include "lambertian.h"
#include "hittable.h"

bool lambertian::scatter(const ray &ray_in, const hitdata &rec, color &attenuation, ray &scattered_ray) const
{
    point3 diffuse_target = rec.normal + random_inside_unit_sphere().normalize();

    if (diffuse_target.near_zero())
        diffuse_target = rec.normal;

    scattered_ray = ray(rec.hit_position, diffuse_target);

    attenuation = m_albedo;
    return true;
}