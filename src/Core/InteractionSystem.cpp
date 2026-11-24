#include "Core/InteractionSystem.h"

#include "Interfaces/IInteractable.h"

#include <cfloat>

InteractionSystem::InteractionSystem()
{

}

void InteractionSystem::Update(const PlayerController& player, Scene& scene, InputManager& inputManager)
{
    if (!inputManager.IsKeyPressed(GLFW_KEY_E))
        return;

    IInteractable* closestInteractable = nullptr;
    float minDistanceSquared = FLT_MAX;

    const glm::vec3 playerPos = player.GetWorldCollider().center;
    for (IInteractable* interactable : scene.GetInteractables())
    {
        // A different way of implementing (x1-x2)^2 + (y1-y2)^2 + (z1-z2)^2
        glm::vec3 difference = playerPos - interactable->GetWorldInteractionSphere().center;
        float distanceSquared = glm::dot(difference, difference);

        float radius = interactable->GetWorldInteractionSphere().radius;

        if ((distanceSquared <= radius * radius) && (distanceSquared < minDistanceSquared)) 
        {
            minDistanceSquared = distanceSquared;
            closestInteractable = interactable;
        }
    }

    if (closestInteractable != nullptr)
    {
        closestInteractable->Interact();
    }
}