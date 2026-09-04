#include "Scene/GameObject.h"

GameObject::GameObject(Model& modelRef)
    : RenderObject(modelRef)
{

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