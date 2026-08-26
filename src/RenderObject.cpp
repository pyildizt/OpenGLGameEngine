#include "RenderObject.h"

RenderObject::RenderObject(Model& modelRef)
    : model(modelRef)
{
    isActive = true;
    transform = Transform{}; 
}

void RenderObject::SetActive(bool newVal)
{
    isActive = newVal;
}

bool RenderObject::IsActive() const
{
    return isActive;
}

Model& RenderObject::GetModel() const
{
    return model;
}

Transform& RenderObject::GetTransform()
{
    return transform;
}

const Transform& RenderObject::GetTransform() const
{
    return transform;
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