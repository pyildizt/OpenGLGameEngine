#ifndef RENDERER_H
#define RENDERER_H

#include "Camera.h"
#include "CameraFixedObject.h"
#include "Object.h"
#include "Projection.h"
#include "Scene.h"
#include "Shader.h"

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
    void DrawObject(const Object& object);
    void DrawCameraFixedObject(CameraFixedObject& cameraFixedObject, Camera& cameraRef);

    void RenderScene(Scene& scene);
};

#endif