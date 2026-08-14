#ifndef OBJECT_H
#define OBJECT_H

#include "Model.h"
#include "Transform.h"

class Object
{
private:
    Model* model;
    Transform transform;

public:
    Object(Model& modelRef);

    Model& GetModel() const;
    Transform& GetTransform();

    void DrawObject();
};

#endif