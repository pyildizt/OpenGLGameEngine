#ifndef ANIMATION_SYSTEM_H
#define ANIMATION_SYSTEM_H

#include "Core/Scene.h"

class AnimationSystem
{
public:
    AnimationSystem();

    void Update(Scene& scene, float deltaTime);
};

#endif