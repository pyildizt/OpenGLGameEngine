#include "Object.h"

#include "Model.h"
#include "Transform.h"

Object::Object(Model& modelRef)
{
    isActive = true;
    model = &modelRef;
    transform = Transform{}; 
}

void Object::SetActive(bool newVal)
{
    isActive = newVal;
}

bool Object::IsActive() const
{
    return isActive;
}

Model& Object::GetModel() const
{
    return *model;
}

Transform& Object::GetTransform()
{
    return transform;
}


void Object::DrawObject()
{
    model->DrawModel();
}