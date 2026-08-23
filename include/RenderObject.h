#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include "Model.h"
#include "Transform.h"

class RenderObject
{
private:
    bool isActive{true};
    Model& model;
    Transform transform;

public:
    RenderObject(Model& modelRef);

    void SetActive(bool newVal);
    bool IsActive() const;

    Model& GetModel() const;
    Transform& GetTransform();
    const Transform& GetTransform() const;

    void DrawObject() const;
};

#endif