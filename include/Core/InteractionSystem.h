#ifndef INTERACTION_SYSTEM_H
#define INTERACTION_SYSTEM_H

#include "Core/PlayerController.h"
#include "Core/Scene.h"

class InteractionSystem
{
public:
    InteractionSystem();

    void Update(const PlayerController& player, Scene& scene, InputManager& inputManager);
};

#endif