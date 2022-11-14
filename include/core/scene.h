#ifndef SCENE_H
#define SCENE_H

#include "core/camera.h"
#include "objects/group.h"
#include "common.h"

struct scene
{
    std::vector<camera> cameras;
    std::shared_ptr<group> objects;
};

#endif