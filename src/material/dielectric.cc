#include "material/dielectric.h"

bool dielectric::scatter(const ray &ray_in, const hitdata &rec, glm::vec3 &attenuation, ray &scattered_ray) const
{
    attenuation = glm::vec3(1.0f);
    float etai_over_etao = rec.front_face ? (1.0 / m_ir_index) : m_ir_index;

    glm::vec3 unit_dir = glm::normalize(ray_in.direction());

    float cos_theta = fmin(glm::dot(-unit_dir, rec.normal), 1.0);
    float sin_theta = glm::sqrt(1 - cos_theta * cos_theta);

    bool total_internal_reflection = etai_over_etao * sin_theta > 1.0f;
    if (total_internal_reflection || schlick_reflectance(cos_theta, etai_over_etao) > random_float())
    {
        // reflect
        scattered_ray = ray(rec.hit_position, glm::reflect(unit_dir, rec.normal));
    }
    else
    {
        // refract

        scattered_ray = ray(rec.hit_position, glm::refract(unit_dir, rec.normal, etai_over_etao));
    }
    return true;
}

float dielectric::schlick_reflectance(float cos_theta, float etai_over_etao)
{
    // Use Schlick's approximation for reflectance.
    auto r0 = (1 - etai_over_etao) / (1 + etai_over_etao);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cos_theta), 5);
}