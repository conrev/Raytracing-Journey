#include "objects/group.h"

bool group::hit(const ray &raySource, float t_min, float t_max, hitdata &hitInfo) const
{
    float min_t = t_max;
    bool hit_anything = false;

    for (const auto &obj : m_objects)
    {
        hitdata temp;
        bool intersect = obj->hit(raySource, t_min, min_t, temp);
        if (intersect)
        {
            hit_anything = true;
            hitInfo = temp;
            min_t = temp.t;
        }
    }

    return hit_anything;
}

void group::add_object(std::shared_ptr<hittable> obj)
{
    m_objects.push_back(obj);
}
