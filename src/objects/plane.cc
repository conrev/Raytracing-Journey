#include "objects/plane.h"

bool plane::hit(const ray &raySource, float t_min, float t_max, hitdata &hitInfo) const
{
    float denom = dot(raySource.direction(), m_normal);
    float t = 0;

    if (std::abs(denom) > 1e-8)
    {

        glm::vec3 start_dif = m_point_in_plane - raySource.origin();
        t = glm::dot(start_dif, m_normal) / denom;

        if (t >= t_min && t <= t_max)
        {
            // std::cerr << "hit" << std::endl;
            hitInfo.hit_position = raySource.eval(t);
            hitInfo.set_face_normal(raySource, m_normal);
            hitInfo.hit_material = m_material;
            return true;
        }
    }
    return false;
}