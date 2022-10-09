#include "sphere.h"

bool sphere::hit(const ray &raySource, double t_min, double t_max, hitdata &hitInfo) const
{
    double a = raySource.direction().length_squared();
    vec3 aminc = raySource.origin() - m_center;
    double half_b = dot(raySource.direction(), aminc);
    double c = aminc.length_squared() - m_radius * m_radius;

    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return false;

    double discriminant_root = sqrt(discriminant);
    double root = (-half_b - discriminant_root) / a;
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
    hitInfo.normal = (hitInfo.hit_position - m_center).normalize();

    return true;
}