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
    glm::vec4 color{1.0f};
    bool useTexture{true};

public:
    RenderObject(Model& modelRef);

    void SetActive(bool newVal);
    bool IsActive() const;

    Model& GetModel() const;
    Transform& GetTransform();
    const Transform& GetTransform() const;

    void SetColor(glm::vec4 newColor);
    glm::vec4 GetColor() const;

    void UseTexture(bool newVal);
    bool IsUsingTexture() const;

    void DrawObject() const;
};

#endif