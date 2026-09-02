#ifndef COLLIDER_RENDERER_H
#define COLLIDER_RENDERER_H

#include "Core/Scene.h"
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"

class ColliderRenderer
{
private:
    bool showColliders{};
    GLuint boxColliderVAO{};
    GLuint boxColliderVBO{};
    GLuint boxColliderEBO{};

public:
    ColliderRenderer();

    void SetShowColliders(bool newVal);
    bool ShowColliders() const;

    void InitializeColliders();

    void DrawCollider(const ICollidable& collidable, Shader& shader);
    void DrawColliders(Scene& scene, Shader& shader);
};

#endif