#include "GameObject.h"

int GameObject::gameObjectCount = 0;

GameObject::GameObject(Model& modelRef)
    : RenderObject(modelRef)
{
    gameObjectID = gameObjectCount++;
}

int GameObject::GetGameObjectID() const
{
    return gameObjectID;
}

void GameObject::SetObjectName(const std::string& newName)
{
    objectName = newName;
}

const std::string& GameObject::GetObjectName() const
{
    return objectName;
}

void GameObject::SetCollider(const Collider& newCollider)
{
    collider = newCollider;
}

/// <summary>
/// Translate from collider's local bounds to world bounds
/// </summary>
Collider GameObject::GetWorldCollider() const
{
    Collider worldCollider = collider;

    worldCollider.center += GetLocalTransform().positionVector;
    worldCollider.halfSize = collider.halfSize * GetLocalTransform().scaleVector;
    worldCollider.radius = collider.radius * GetLocalTransform().scaleVector.y;

    return worldCollider;
}