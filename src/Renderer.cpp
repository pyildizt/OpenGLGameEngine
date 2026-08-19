#include "Renderer.h"

Renderer::Renderer(Shader& shaderRef, Projection& projectionRef, Camera& cameraRef)
{
    shader = &shaderRef;
    projection = &projectionRef;
    camera = &cameraRef;

    shader->SetMat4(shader->GetUniformLocation("projection"), projection->GetProjection());
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

void Renderer::SetProjection(Projection& newProjection)
{
    projection = &newProjection;
}

Projection& Renderer::GetProjection() const
{
    return *projection;
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
    shader->SetMat4(shader->GetUniformLocation("projection"), projection->GetProjection());
    shader->SetMat4(shader->GetUniformLocation("view"), camera->GetViewMatrix());    
}

void Renderer::DrawObject(Object& object) const
{
    shader->SetMat4(shader->GetUniformLocation("model"), object.GetTransform().GetMatrix());
    object.DrawObject();
}