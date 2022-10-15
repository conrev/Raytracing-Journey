#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "vec3.h"
#include "hittable.h"

class lambertian : public material
{
public:
    lambertian() = default;
    lambertian(const color &albedo) : m_albedo(albedo) {}
    virtual bool scatter(const ray &ray_in, const hitdata &rec, color &attenuation, ray &scattered_ray) const override;

private:
    color m_albedo;
};

#endif