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

void Renderer::SetShowColliders(bool newVal)
{
    showColliders = newVal;
}

bool Renderer::ShowColliders() const
{
    return showColliders;
}

void Renderer::BeginFrame()
{
    glClearColor(0.20f, 0.15f, 0.18f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->SetMat4(shader->GetUniformLocation("projection"), projection.GetProjection());
    shader->SetMat4(shader->GetUniformLocation("view"), camera->GetViewMatrix());    
}

void Renderer::DrawObject(const Object& object)
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

void Renderer::DrawCollider(const Collider& collider) const
{
    // TODO: 
}

void Renderer::RenderScene(Scene& scene)
{
    BeginFrame();

    for (const Object& object : scene.GetObjects())
    {
        if (object.IsActive())
        {
            DrawObject(object);
            if (showColliders)
            {
                DrawCollider(object.GetWorldCollider());
            }
        }
    }
    for (CameraFixedObject& cameraFixedObject : scene.GetCameraFixedObjects())
    {
        if (cameraFixedObject.IsActive())
        {
            cameraFixedObject.GetTransform().Translate(glm::vec3{0.0f, 0.0f, -0.1f});
            
            //FIXME: DrawCameraFixedObject(cameraFixedObject, cameraFixedObject.GetCamera());  
            DrawCameraFixedObject(cameraFixedObject, GetCamera());  
        }  
    }
}