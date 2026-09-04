#include "Rendering/Renderer.h"
#include "Rendering/PickingRenderer.h"

Renderer::Renderer()
    : projection(), sceneRenderer(), colliderRenderer()
{

}

Renderer::Renderer(Shader& shader, Camera& camera)
    : shader(&shader), projection(), camera(&camera), sceneRenderer(), colliderRenderer()
{
    shader.SetMat4(shader.GetUniformLocation("projection"), projection.GetProjection());
    shader.SetMat4(shader.GetUniformLocation("view"), camera.GetViewMatrix());
}

void Renderer::InitializeRenderer(Shader& shaderRef, Camera &cameraRef)
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

SceneRenderer& Renderer::GetSceneRenderer()
{
    return sceneRenderer;
}

const SceneRenderer& Renderer::GetSceneRenderer() const
{
    return sceneRenderer;
}

PickingRenderer& Renderer::GetPickingRenderer()
{
    return pickingRenderer;
}

const PickingRenderer& Renderer::GetPickingRenderer() const
{
    return pickingRenderer;
}

ColliderRenderer& Renderer::GetColliderRenderer()
{
    return colliderRenderer;
}

const ColliderRenderer& Renderer::GetColliderRenderer() const
{
    return colliderRenderer;
}

GridRenderer& Renderer::GetGridRenderer()
{
    return gridRenderer;
}

const GridRenderer& Renderer::GetGridRenderer() const
{
    return gridRenderer;
}

void Renderer::RenderScene(Scene& scene)
{
    glClearColor(0.20f, 0.15f, 0.18f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sceneRenderer.RenderScene(scene, *shader, projection, *camera);
    colliderRenderer.DrawColliders(scene, *shader);
    gridRenderer.DrawGrid(*shader);
}