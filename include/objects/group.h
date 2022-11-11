#ifndef GROUP_H
#define GROUP_H

#include "core/hittable.h"
#include "common.h"

class group : public hittable
{
public:
    virtual bool hit(const ray &raySource, float t_min, float t_max, hitdata &hitInfo) const override;
    void add_object(std::shared_ptr<hittable> obj);

private:
    std::vector<std::shared_ptr<hittable>> m_objects;
};
#endif