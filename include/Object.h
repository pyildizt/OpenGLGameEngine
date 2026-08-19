#ifndef OBJECT_H
#define OBJECT_H

#include "Model.h"
#include "Transform.h"

class Object
{
private:
    bool isActive{true};
    Model* model;
    Transform transform;

public:
    Object(Model& modelRef);

    void SetActive(bool newVal);
    bool IsActive() const;

    Model& GetModel() const;
    Transform& GetTransform();

    void DrawObject();
};

#endif