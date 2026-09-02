#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Interfaces/ICollidable.h"
#include "Scene/RenderObject.h"

#include <string>

class GameObject : public RenderObject, public ICollidable
{
private:
    int gameObjectID;

    std::string objectName{};

    Collider collider;

public:
    static int gameObjectCount;

    GameObject(Model& modelRef);

    int GetGameObjectID() const;

    void SetObjectName(const std::string& newName);
    const std::string& GetObjectName() const;

    void SetCollider(const Collider& newCollider);
    Collider GetWorldCollider() const override;
};

#endif