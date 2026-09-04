#ifndef RENDERER_H
#define RENDERER_H

#include "Camera/Camera.h"
#include "Camera/Projection.h"
#include "Core/Scene.h"
#include "Rendering/ColliderRenderer.h"
#include "Rendering/GridRenderer.h"
#include "Rendering/PickingRenderer.h"
#include "Rendering/SceneRenderer.h"
#include "Rendering/Shader.h"

class Renderer
{
private:
    Shader* shader;
    Projection projection;
    Camera* camera;

    SceneRenderer sceneRenderer;
    PickingRenderer pickingRenderer;
    ColliderRenderer colliderRenderer;
    GridRenderer gridRenderer;

public:
    Renderer();
    Renderer(Shader& shaderRef, Camera &cameraRef);

    void InitializeRenderer(Shader& shaderRef, Camera &cameraRef);

    void SetShader(Shader& newShader);
    Shader& GetShader() const;

    Projection& GetProjection();

    void SetCamera(Camera& newCamera);
    Camera& GetCamera() const;

    SceneRenderer& GetSceneRenderer();
    const SceneRenderer& GetSceneRenderer() const;

    PickingRenderer& GetPickingRenderer();
    const PickingRenderer& GetPickingRenderer() const;
    
    ColliderRenderer& GetColliderRenderer();
    const ColliderRenderer& GetColliderRenderer() const;

    GridRenderer& GetGridRenderer();
    const GridRenderer& GetGridRenderer() const;

    void RenderScene(Scene& scene);
};

#endif