#include "CameraFixedObject.h"

CameraFixedObject::CameraFixedObject(Model& modelRef)
    : RenderObject(modelRef)
{

}

CameraFixedObject::CameraFixedObject(Camera& cameraRef, Model& modelRef)
    : RenderObject(modelRef)
{
    camera = &cameraRef;
}

void CameraFixedObject::SetCamera(Camera& cameraRef)
{
    camera = &cameraRef;
}

Camera& CameraFixedObject::GetCamera() const
{
    return *camera;
}

glm::mat4 CameraFixedObject::GetMatrix()
{
    glm::mat4 lookAt{1.0f};
    //FIXME:
    // lookAt[0] = glm::vec4(camera->GetRightVector(), 0.0f);
    // lookAt[1] = glm::vec4(camera->GetUpVector(), 0.0f);
    // lookAt[2] = glm::vec4(-camera->GetForwardVector(), 0.0f);
    // lookAt[3] = glm::vec4(camera->GetPositionVector() + camera->GetForwardVector() * 4.5f, 1.0f);

    return lookAt * GetLocalTransform().GetMatrix();
}