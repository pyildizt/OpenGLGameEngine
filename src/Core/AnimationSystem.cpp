#include "Core/AnimationSystem.h"

#include "Core/Scene.h"

AnimationSystem::AnimationSystem()
{

}

void AnimationSystem::Update(Scene& scene, float deltaTime)
{
    for (IAnimatable* animatable : scene.GetAnimatables())
    {
        animatable->Update(deltaTime);
    }
}