#include "Rendering/ColliderRenderer.h"

#include "Interfaces/ICollidable.h"
#include "Utilities/Utils.h"

ColliderRenderer::ColliderRenderer()
{
    InitializeColliders();
}

void ColliderRenderer::SetShowColliders(bool newVal)
{
    showColliders = newVal;
}

bool ColliderRenderer::ShowColliders() const
{
    return showColliders;
}

void ColliderRenderer::InitializeColliders()
{
    // Box collider vertices and indices
    GLfloat boxVertices[] = {
        // Front face
        -0.5f,  -0.5f,  -0.5f,    // 0
        0.5f,   -0.5f,  -0.5f,    // 1
        0.5f,   0.5f,   -0.5f,    // 2
        -0.5f,  0.5f,   -0.5f,  // 3

        // Back face
        -0.5f,  -0.5f,  0.5f,  // 4
        0.5f,   -0.5f,  0.5f,  // 5
        0.5f,   0.5f,   0.5f,  // 6
        -0.5f,  0.5f,   0.5f   // 7
    };
    GLuint boxIndices[] = {
        // Front
        0, 1, 2,
        2, 3, 0,

        // Back
        4, 5, 6,
        6, 7, 4,

        // Left
        0, 3, 7,
        7, 4, 0,

        // Right
        1, 5, 6,
        6, 2, 1,

        // Bottom
        0, 4, 5,
        5, 1, 0,

        // Top
        3, 2, 6,
        6, 7, 3
    };

    // Create and bind VAO, VBOs and EBO
    glGenVertexArrays(1, &boxColliderVAO);
    glBindVertexArray(boxColliderVAO);

    glGenBuffers(1, &boxColliderVBO);
    glBindBuffer(GL_ARRAY_BUFFER, boxColliderVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW);
  
    glGenBuffers(1, &boxColliderEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boxColliderEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boxIndices), boxIndices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &boxColliderEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boxColliderEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boxIndices), boxIndices, GL_STATIC_DRAW);
}

void ColliderRenderer::DrawCollider(const ICollidable& collidable, Shader& shader)
{
    if (showColliders)
    {
        Collider collider = collidable.GetWorldCollider();
        if (collider.colliderShape == ColliderShape::Box)
        {
            glm::mat4 transform{1.0f};
            transform = glm::translate(transform, collider.center);
            transform = glm::scale(transform, collider.halfSize * 2.0f);

            shader.SetMat4(shader.GetUniformLocation("model"), transform);
            shader.SetBool(shader.GetUniformLocation("useTexture"), false);
            shader.SetVec4(shader.GetUniformLocation("objectColor"), RGBAtoVec4(17, 242, 85, 255));

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glBindVertexArray(boxColliderVAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        } 
    }
}

void ColliderRenderer::DrawColliders(Scene& scene, Shader& shader)
{
    if (showColliders)
    {
        for (const GameObject* gameObject : scene.GetGameObjects())
        {
            if (gameObject->IsActive())
            {
                DrawCollider(*gameObject, shader);
            }
        }
    }
}