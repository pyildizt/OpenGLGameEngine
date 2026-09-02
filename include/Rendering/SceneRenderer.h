#ifndef SCENE_RENDERER_H
#define SCENE_RENDERER_H

#include "Camera/Camera.h"
#include "Camera/Projection.h"
#include "Core/Scene.h"
#include "Scene/RenderObject.h"

class SceneRenderer
{
public:
    SceneRenderer();

    void DrawRenderObject(const RenderObject& renderObject, Shader& shader);

    void RenderNode(const SceneNode& sceneNode, Shader& shader);
    void RenderScene(Scene& scene, Shader& shader, Projection& projection, Camera& camera);
};

#endif