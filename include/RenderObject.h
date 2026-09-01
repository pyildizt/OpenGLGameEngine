#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include "Model.h"
#include "SceneNode.h"

class RenderObject : public SceneNode
{
private:
    Model& model;
    glm::vec4 color{1.0f};
    bool useTexture{true};

public:
    RenderObject(Model& modelRef);

    Model& GetModel() const;

    void SetColor(glm::vec4 newColor);
    glm::vec4 GetColor() const;

    void UseTexture(bool newVal);
    bool IsUsingTexture() const;

    void DrawObject() const;
};

#endif