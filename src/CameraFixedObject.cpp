#include "CameraFixedObject.h"

#include "Model.h"
#include "Transform.h"

CameraFixedObject::CameraFixedObject(Model& modelRef)
{
    isActive = true;
    model = &modelRef;
    transform = Transform{}; 
}

CameraFixedObject::CameraFixedObject(Camera& cameraRef, Model& modelRef)
{
    isActive = true;
    camera = &cameraRef;
    model = &modelRef;
    transform = Transform{}; 
}

void CameraFixedObject::SetActive(bool newVal)
{
    isActive = newVal;
}

bool CameraFixedObject::IsActive() const
{
    return isActive;
}

void CameraFixedObject::SetCamera(Camera& cameraRef)
{
    camera = &cameraRef;
}

Camera& CameraFixedObject::GetCamera() const
{
    return *camera;
}

Model& CameraFixedObject::GetModel() const
{
    return *model;
}

Transform& CameraFixedObject::GetTransform()
{
    return transform;
}

glm::mat4 CameraFixedObject::GetMatrix()
{
    glm::mat4 lookAt{1.0f};
    lookAt[0] = glm::vec4(camera->GetRightVector(), 0.0f);
    lookAt[1] = glm::vec4(camera->GetUpVector(), 0.0f);
    lookAt[2] = glm::vec4(-camera->GetForwardVector(), 0.0f);
    lookAt[3] = glm::vec4(camera->GetPositionVector() + camera->GetForwardVector() * 4.5f, 1.0f);

    return lookAt * transform.GetMatrix();
}

void CameraFixedObject::DrawObject() const
{
    model->DrawModel();
}