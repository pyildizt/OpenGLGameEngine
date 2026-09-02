#ifndef RENDERER_H
#define RENDERER_H

#include "Camera/Camera.h"
#include "Camera/Projection.h"
#include "Core/Scene.h"
#include "Rendering/Shader.h"
#include "Scene/CameraFixedObject.h"
#include "Scene/RenderObject.h"

class Renderer
{
private:
    Shader* shader;
    Projection projection;
    Camera* camera;

    bool showColliders{};
    GLuint boxColliderVAO, boxColliderVBO, boxColliderEBO;

public:
    Renderer();
    Renderer(Shader& shaderRef, Camera& cameraRef);

    void InitializeRenderer(Shader& shaderRef, Camera& cameraRef);

    void SetShader(Shader& newShader);
    Shader& GetShader() const;

    Projection& GetProjection();

    void SetCamera(Camera& newCamera);
    Camera& GetCamera() const;

    void SetShowColliders(bool newVal);
    bool ShowColliders() const;
    void InitializeColliders();
    void DrawCollider(const ICollidable& collidable);
    void DrawColliders(Scene& scene);

    void BeginFrame();
    void DrawRenderObject(const RenderObject& renderObject);
    void DrawCameraFixedObject(CameraFixedObject& cameraFixedObject, Camera& cameraRef);

    void RenderNode(const SceneNode& sceneNode);
    void RenderScene(Scene& scene);
};

#endif