#ifndef METAL_H
#define METAL_H

#include "material.h"
#include "vec3.h"
#include "hittable.h"

class metal : public material
{
public:
    metal() = default;
    metal(const color &albedo, double fuzziness) : m_albedo(albedo), m_fuzziness(fuzziness) {}
    virtual bool scatter(const ray &ray_in, const hitdata &rec, color &attenuation, ray &scattered_ray) const override;

private:
    color m_albedo;
    double m_fuzziness;
};

#endif