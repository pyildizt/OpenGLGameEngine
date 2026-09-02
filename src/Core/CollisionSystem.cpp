#include "Core/CollisionSystem.h"

#include "Core/PlayerController.h"
#include "Interfaces/ICollidable.h"
#include "Scene/GameObject.h"

#include <iostream>

CollisionSystem::CollisionSystem()
{

}

void CollisionSystem::Update(PlayerController& playerController, Scene& scene)
{
    for (GameObject* gameObject : scene.GetGameObjects())
    {
        if (DetectCollision(playerController, *gameObject))
        {
            std::cout << "COLLISION with " << gameObject->GetGameObjectID() << ": " << gameObject->GetObjectName() << "\n";
            HandleCollision(playerController, *gameObject);
        }
    }
}

bool CollisionSystem::DetectCollision(const ICollidable& collidableA, const ICollidable& collidableB) const
{
    Collider colliderA = collidableA.GetWorldCollider();
    Collider colliderB = collidableB.GetWorldCollider();

    // Box to box collision detection
    if (colliderA.colliderShape == ColliderShape::Box && 
        colliderB.colliderShape == ColliderShape::Box)
    {
        // min: x = centerA.x - halfSize.x, max: x = centerA.x + halfSize.x
        // min: y = centerA.y - halfSize.y, max: y = centerA.y + halfSize.y
        // ... then check if (maxA >= minB && minA <= maxB) for all axes

        glm::vec3 minA = colliderA.center - colliderA.halfSize;
        glm::vec3 maxA = colliderA.center + colliderA.halfSize;

        glm::vec3 minB = colliderB.center - colliderB.halfSize;
        glm::vec3 maxB = colliderB.center + colliderB.halfSize;

        if (maxA.x >= minB.x && minA.x <= maxB.x &&
            maxA.y >= minB.y && minA.y <= maxB.y &&
            maxA.z >= minB.z && minA.z <= maxB.z)
        {
            return true;
        }
    }
    //TODO: Handle box-to-sphere and sphere-to-sphere collisions
    return false;
}

void CollisionSystem::HandleCollision(PlayerController& playerController, const ICollidable& collidable)
{
    Collider playerCollider = playerController.GetWorldCollider();
    Collider objCollider = collidable.GetWorldCollider();

    // Assume true for box to box detection
    if (playerCollider.colliderShape == ColliderShape::Box && 
        objCollider.colliderShape == ColliderShape::Box)
    {
        glm::vec3 minPlayer = playerCollider.center - playerCollider.halfSize;
        glm::vec3 maxPlayer = playerCollider.center + playerCollider.halfSize;

        glm::vec3 minObj = objCollider.center - objCollider.halfSize;
        glm::vec3 maxObj = objCollider.center + objCollider.halfSize;

        glm::vec3 collisionAmount{};
        collisionAmount.x = glm::min(maxPlayer.x - minObj.x, maxObj.x - minPlayer.x);
        collisionAmount.y = glm::min(maxPlayer.y - minObj.y, maxObj.y - minPlayer.y);
        collisionAmount.z = glm::min(maxPlayer.z - minObj.z, maxObj.z - minPlayer.z);
        //std::cout << "Collision amount: (" << collisionAmount.x << ", " << collisionAmount.y << ", " << collisionAmount.z << ")\n";

        // Move player collision amount in the opposite direction of the smallest collision
        if (collisionAmount.x <= collisionAmount.z && collisionAmount.x <= collisionAmount.y)
        {
            float movementDirection = playerCollider.center.x < objCollider.center.x ? -1.0f : 1.0f;
            playerController.GetPlayerCamera().GetLocalTransform().Translate(glm::vec3{movementDirection * collisionAmount.x, 0.0f, 0.0f});
        }
        else if (collisionAmount.z < collisionAmount.x && collisionAmount.z <= collisionAmount.y)
        {
            float movementDirection = playerCollider.center.z < objCollider.center.z ? -1.0f : 1.0f;
            playerController.GetPlayerCamera().GetLocalTransform().Translate(glm::vec3{0.0f, 0.0f, movementDirection * collisionAmount.z});
        }
        else 
        {
            float movementDirection = playerCollider.center.y < objCollider.center.y ? -1.0f : 1.0f;
            playerController.GetPlayerCamera().GetLocalTransform().Translate(glm::vec3{0.0f, movementDirection * collisionAmount.y, 0.0f});
        }
    }
    //TODO: Handle box-to-sphere and maybe sphere-to-sphere collisions
}