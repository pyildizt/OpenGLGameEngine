#ifndef RENDERER_H
#define RENDERER_H

#include "Camera.h"
#include "CameraFixedObject.h"
#include "Object.h"
#include "Projection.h"
#include "Shader.h"

class Renderer
{
private:
    Shader* shader;
    Projection* projection;
    Camera* camera;

public:
    Renderer(Shader& shaderRef, Projection& projectionRef, Camera& cameraRef);

    void SetShader(Shader& newShader);
    Shader& GetShader() const;

    void SetProjection(Projection& newProjection);
    Projection& GetProjection() const;

    void SetCamera(Camera& newCamera);
    Camera& GetCamera() const;

    void BeginFrame();
    void DrawObject(Object& object) const;
    void DrawCameraFixedObject(CameraFixedObject& cameraFixedObject) const;
};

#endif