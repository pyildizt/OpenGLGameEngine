#ifndef PICKING_RENDERER_H
#define PICKING_RENDERER_H

#include "Camera/Projection.h"
#include "Core/Scene.h"
#include "Rendering/Shader.h"
#include "Scene/RenderObject.h"

class PickingRenderer
{
private:
    Shader* shader{nullptr};

public:
    PickingRenderer();

    void SetShader(Shader& newShader);
    Shader& GetShader() const;

    void DrawRenderObjectWithPicking(const RenderObject& renderObject);

    void RenderNode(const SceneNode& sceneNode);
    void RenderScene(Scene& scene, Projection& projection, Camera& camera);

    unsigned int ColorToID(const unsigned char pixel[4]);
    glm::vec4 IDToColor(unsigned int id);
};

#endif