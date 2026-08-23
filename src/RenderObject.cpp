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

void RenderObject::DrawObject() const
{
    model.DrawModel();
}