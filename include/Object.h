#ifndef OBJECT_H
#define OBJECT_H

#include "ICollidable.h"
#include "RenderObject.h"

class Object : public RenderObject, public ICollidable
{
private:
    int objectID;

    Collider collider;

public:
    static int objectCount;

    Object(Model& modelRef);

    int GetObjectID() const;

    void SetCollider(const Collider& newCollider);
    Collider GetWorldCollider() const override;
};

#endif