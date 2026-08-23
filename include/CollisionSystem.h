#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "ICollidable.h"

#include "PlayerController.h"
#include "Scene.h"

class CollisionSystem
{
public:
    CollisionSystem();

    void Update(PlayerController& playerController, Scene& scene);

    bool DetectCollision(const ICollidable& collidableA, const ICollidable& collidableB) const;

    void HandleCollision(PlayerController& playerController, const ICollidable& collidableB);
};

#endif