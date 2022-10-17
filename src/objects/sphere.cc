#include "glm/gtx/norm.hpp"

#include "objects/sphere.h"

bool sphere::hit(const ray &raySource, float t_min, float t_max, hitdata &hitInfo) const
{
    float a = glm::length2(raySource.direction());
    glm::vec3 aminc = raySource.origin() - m_center;
    float half_b = dot(raySource.direction(), aminc);
    float c = glm::length2(aminc) - m_radius * m_radius;

    float discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return false;

    float discriminant_root = sqrt(discriminant);
    float root = (-half_b - discriminant_root) / a;
    if (root < t_min || t_max < root)
    {
        // first root doesn't satisfy, check 2nd root
        root = (-half_b + discriminant_root) / a;
        if (root < t_min || t_max < root)
            // no root in desired range
            return false;
    }
    hitInfo.t = root;
    hitInfo.hit_position = raySource.eval(root);
    glm::vec3 outward_normal = glm::normalize(hitInfo.hit_position - m_center);
    hitInfo.set_face_normal(raySource, outward_normal);
    hitInfo.hit_material = m_material;

    return true;
}