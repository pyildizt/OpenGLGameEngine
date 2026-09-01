#include "RenderObject.h"

RenderObject::RenderObject(Model& modelRef)
    : SceneNode(), model(modelRef)
{

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