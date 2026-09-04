#include "Rendering/PickingRenderer.h"

PickingRenderer::PickingRenderer()
{

}

void PickingRenderer::SetShader(Shader& newShader)
{
    shader = &newShader;
}

Shader& PickingRenderer::GetShader() const
{
    return *shader;
}

void PickingRenderer::DrawRenderObjectWithPicking(const RenderObject& renderObject)
{
    shader->SetMat4(shader->GetUniformLocation("model"), renderObject.GetWorldMatrix());
    shader->SetVec4(shader->GetUniformLocation("uniquePickingColor"), IDToColor(renderObject.GetPickingID()));
    renderObject.DrawObject();
}

void PickingRenderer::RenderNode(const SceneNode& sceneNode)
{
    if (!sceneNode.IsActive())
    {
        return;
    }

    // Only render the RenderObject subclass of SceneNodes
    if (const RenderObject* renderObject = dynamic_cast<const RenderObject*>(&sceneNode))
    {
        DrawRenderObjectWithPicking(*renderObject);
    }

    // Render children nodes recursively
    for (const SceneNode* child : sceneNode.GetChildren())
    {
        RenderNode(*child);
    }
}

void PickingRenderer::RenderScene(Scene& scene, Projection& projection, Camera& camera)
{
    shader->ActivateShaderProgram();
    shader->SetMat4(shader->GetUniformLocation("projection"), projection.GetProjection());
    shader->SetMat4(shader->GetUniformLocation("view"), camera.GetViewMatrix());    

    for (const auto& node : scene.GetSceneNodes())
    {
        RenderNode(*node);
    }
}

unsigned int PickingRenderer::ColorToID(const unsigned char pixel[4])
{
    return static_cast<unsigned int>(pixel[0])
         | (static_cast<unsigned int>(pixel[1]) << 8)
         | (static_cast<unsigned int>(pixel[2]) << 16);
}

glm::vec4 PickingRenderer::IDToColor(unsigned int id)
{
    return glm::vec4{
        ((id >> 0) & 0xFF) / 255.0f,
        ((id >> 8) & 0xFF) / 255.0f,
        ((id >> 16) & 0xFF) / 255.0f,
        1.0f
    };
}