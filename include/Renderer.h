#ifndef RENDERER_H
#define RENDERER_H

#include "Camera.h"
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

    void SetShader(const Shader& newShader);
    Shader& GetShader() const;

    void SetProjection(const Projection& newProjection);
    Projection& GetProjection() const;

    void SetCamera(const Camera& newCamera);
    Camera& GetCamera() const;

    void DrawObject(Object& object) const;
};

#endif