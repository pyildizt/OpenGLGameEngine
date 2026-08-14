#include "Renderer.h"

Renderer::Renderer(Shader& shaderRef, Projection& projectionRef, Camera& cameraRef)
{
    shader = &shaderRef;
    projection = &projectionRef;
    camera = &cameraRef;

    shader->SetMat4(shader->GetUniformLocation("projection"), projection->GetProjection());
    shader->SetMat4(shader->GetUniformLocation("view"), camera->GetViewMatrix());
}

void Renderer::SetShader(const Shader& newShader)
{
    *shader = newShader;
}

Shader& Renderer::GetShader() const
{
    return *shader;
}

void Renderer::SetProjection(const Projection& newProjection)
{
    *projection = newProjection;
    shader->SetMat4(shader->GetUniformLocation("projection"), projection->GetProjection());
}

Projection& Renderer::GetProjection() const
{
    return *projection;
}

void Renderer::SetCamera(const Camera& newCamera)
{
    *camera = newCamera;
    shader->SetMat4(shader->GetUniformLocation("view"), camera->GetViewMatrix());
}

Camera& Renderer::GetCamera() const
{
    return *camera;
}

void Renderer::DrawObject(Object& object) const
{
    shader->SetMat4(shader->GetUniformLocation("model"), object.GetTransform().GetMatrix());
    object.DrawObject();
}