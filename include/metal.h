#ifndef METAL_H
#define METAL_H

#include "material.h"
#include "vec3.h"

class metal : public material
{
public:
    metal() = default;
    metal(const color &albedo) : m_albedo(albedo) {}
    virtual bool scatter(const ray &ray_in, const hitdata &rec, color &attenuation, ray &scattered_ray) const override;

private:
    color m_albedo;
};

#endif