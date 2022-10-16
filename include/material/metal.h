#ifndef METAL_H
#define METAL_H

#include "material.h"
#include "hittable.h"

class metal : public material
{
public:
    metal() = default;
    metal(const glm::vec3 &albedo, float fuzziness) : m_albedo(albedo), m_fuzziness(fuzziness) {}
    virtual bool scatter(const ray &ray_in, const hitdata &rec, glm::vec3 &attenuation, ray &scattered_ray) const override;

private:
    glm::vec3 m_albedo;
    float m_fuzziness;
};

#endif