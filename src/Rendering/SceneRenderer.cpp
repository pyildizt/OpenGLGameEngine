#include "Rendering/SceneRenderer.h"

#include "Camera/Projection.h"
#include "Scene/RenderObject.h"
#include "Scene/SceneNode.h"

SceneRenderer::SceneRenderer()
{

}

void SceneRenderer::DrawRenderObject(const RenderObject& renderObject, Shader& shader)
{
    shader.SetMat4(shader.GetUniformLocation("model"), renderObject.GetWorldMatrix());
    shader.SetBool(shader.GetUniformLocation("useTexture"), renderObject.IsUsingTexture());
    shader.SetVec4(shader.GetUniformLocation("objectColor"), renderObject.GetColor());
    renderObject.DrawObject();
}

// void SceneRenderer::DrawCameraFixedObject(CameraFixedObject& cameraFixedObject, Camera& cameraRef)
// {
//     cameraFixedObject.SetCamera(cameraRef);
//     shader->SetMat4(shader->GetUniformLocation("model"), cameraFixedObject.GetMatrix());
//     shader->SetBool(shader->GetUniformLocation("useTexture"), cameraFixedObject.IsUsingTexture());
//     shader->SetVec4(shader->GetUniformLocation("objectColor"), cameraFixedObject.GetColor());
//     cameraFixedObject.DrawObject();
// }

void SceneRenderer::RenderNode(const SceneNode& sceneNode, Shader& shader)
{
    if (!sceneNode.IsActive())
    {
        return;
    }

    // Only render the RenderObject subclass of SceneNodes
    if (const RenderObject* renderObject = dynamic_cast<const RenderObject*>(&sceneNode))
    {
        DrawRenderObject(*renderObject, shader);
    }

    // Render children nodes recursively
    for (const SceneNode* child : sceneNode.GetChildren())
    {
        RenderNode(*child, shader);
    }
}

void SceneRenderer::RenderScene(Scene& scene, Shader& shader, Projection& projection, Camera& camera)
{
    shader.ActivateShaderProgram();
    shader.SetMat4(shader.GetUniformLocation("projection"), projection.GetProjection());
    shader.SetMat4(shader.GetUniformLocation("view"), camera.GetViewMatrix());    

    for (const auto& node : scene.GetSceneNodes())
    {
        RenderNode(*node, shader);
    }
}