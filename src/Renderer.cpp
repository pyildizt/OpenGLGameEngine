#include "Renderer.h"

#include "CameraFixedObject.h"
#include "Projection.h"

Renderer::Renderer(Shader& shaderRef, Camera& cameraRef)
    : projection()
{
    shader = &shaderRef;
    camera = &cameraRef;

    shader->SetMat4(shader->GetUniformLocation("projection"), projection.GetProjection());
    shader->SetMat4(shader->GetUniformLocation("view"), camera->GetViewMatrix());
}

void Renderer::SetShader(Shader& newShader)
{
    shader = &newShader;
}

Shader& Renderer::GetShader() const
{
    return *shader;
}

Projection& Renderer::GetProjection()
{
    return projection;
}

void Renderer::SetCamera(Camera& newCamera)
{
    camera = &newCamera;
}

Camera& Renderer::GetCamera() const
{
    return *camera;
}

void Renderer::BeginFrame()
{
    shader->SetMat4(shader->GetUniformLocation("projection"), projection.GetProjection());
    shader->SetMat4(shader->GetUniformLocation("view"), camera->GetViewMatrix());    
}

void Renderer::DrawObject(Object& object) const
{
    shader->SetMat4(shader->GetUniformLocation("model"), object.GetTransform().GetMatrix());
    object.DrawObject();
}

void Renderer::DrawCameraFixedObject(CameraFixedObject& cameraFixedObject, Camera& cameraRef)
{
    cameraFixedObject.SetCamera(cameraRef);
    shader->SetMat4(shader->GetUniformLocation("model"), cameraFixedObject.GetMatrix());
    cameraFixedObject.DrawObject();
}