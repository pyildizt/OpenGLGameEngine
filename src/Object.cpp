#include "Object.h"

int Object::objectCount = 0;

Object::Object(Model& modelRef)
    : RenderObject(modelRef)
{
    objectID = objectCount++;
}

int Object::GetObjectID() const
{
    return objectID;
}

void Object::SetCollider(const Collider& newCollider)
{
    collider = newCollider;
}

/// <summary>
/// Translate from collider's local bounds to world bounds
/// </summary>
Collider Object::GetWorldCollider() const
{
    Collider worldCollider = collider;

    worldCollider.center += GetTransform().positionVector;
    worldCollider.halfSize = collider.halfSize * GetTransform().scaleVector;
    worldCollider.radius = collider.radius * GetTransform().scaleVector.y;

    return worldCollider;
}