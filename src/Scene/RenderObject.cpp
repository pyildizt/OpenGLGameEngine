#include "Scene/RenderObject.h"

unsigned int RenderObject::pickingIDCounter = 0;

RenderObject::RenderObject(Model& modelRef)
    : SceneNode(), model(modelRef)
{
    pickingID = ++pickingIDCounter;
}

unsigned int RenderObject::GetPickingID() const
{
    return pickingID;
}

Model& RenderObject::GetModel() const
{
    return model;
}

void RenderObject::SetColor(glm::vec4 newColor)
{
    color = newColor;
}

glm::vec4 RenderObject::GetColor() const
{
    return color;
}

void RenderObject::UseTexture(bool newVal)
{
    useTexture = newVal;
}

bool RenderObject::IsUsingTexture() const
{
    return useTexture;
}

void RenderObject::DrawObject() const
{
    model.DrawModel();
}