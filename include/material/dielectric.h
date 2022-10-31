#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "core/hittable.h"
#include "material.h"

class dielectric : public material
{
public:
    dielectric() = default;
    dielectric(float refraction_index) : m_ir_index(refraction_index){};
    virtual bool scatter(const ray &ray_in, const hitdata &rec, glm::vec3 &attenuation, ray &scattered_ray) const override;

private:
    float m_ir_index;
    static float schlick_reflectance(float cos_theta, float etai_over_etao);
};

#endif