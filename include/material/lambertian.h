#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "core/hittable.h"
#include "material.h"

class lambertian : public material
{
public:
    lambertian() = default;
    lambertian(const glm::vec3 &albedo) : m_albedo(albedo) {}
    virtual bool scatter(const ray &ray_in, const hitdata &rec, glm::vec3 &attenuation, ray &scattered_ray) const override;

private:
    glm::vec3 m_albedo;
};

#endif