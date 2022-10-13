#include "objects/plane.h"

bool plane::hit(const ray &raySource, double t_min, double t_max, hitdata &hitInfo) const
{
    double denom = dot(raySource.direction(), m_normal);
    double t = 0;

    if (std::abs(denom) > 1e-8)
    {

        vec3 start_dif = m_point_in_plane - raySource.origin();
        t = dot(start_dif, m_normal) / denom;

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