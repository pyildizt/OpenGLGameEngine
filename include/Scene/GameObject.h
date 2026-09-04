#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Interfaces/ICollidable.h"
#include "Scene/RenderObject.h"

class GameObject : public RenderObject, public ICollidable
{
private:
    Collider collider;

public:
    GameObject(Model& modelRef);

    void SetCollider(const Collider& newCollider);
    Collider GetWorldCollider() const override;
};

#endif