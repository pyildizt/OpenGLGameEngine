#include "Object.h"

#include "Model.h"
#include "Transform.h"

Object::Object(Model& modelRef)
{
    model = &modelRef;
    transform = Transform{}; 
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