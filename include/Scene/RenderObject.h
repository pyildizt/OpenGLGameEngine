#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include "Rendering/Model.h"
#include "Scene/SceneNode.h"

class RenderObject : public SceneNode
{
private:
    unsigned int pickingID;

    Model& model;
    glm::vec4 color{1.0f};
    bool useTexture{true};

public:
    static unsigned int pickingIDCounter;

    RenderObject(Model& modelRef);

    unsigned int GetPickingID() const;

    Model& GetModel() const;

    void SetColor(glm::vec4 newColor);
    glm::vec4 GetColor() const;

    void UseTexture(bool newVal);
    bool IsUsingTexture() const;

    void DrawObject() const;
};

#endif