#include "Renderer.h"

#include "CameraFixedObject.h"
#include "ICollidable.h"
#include "Projection.h"
#include "Utils.h"

Renderer::Renderer()
    : projection()
{

}

Renderer::Renderer(Shader& shaderRef, Camera& cameraRef)
    : projection()
{
    shader = &shaderRef;
    camera = &cameraRef;

    shader->SetMat4(shader->GetUniformLocation("projection"), projection.GetProjection());
    shader->SetMat4(shader->GetUniformLocation("view"), camera->GetViewMatrix());

    InitializeColliders();
}

void Renderer::InitializeRenderer(Shader& shaderRef, Camera& cameraRef)
{
    shader = &shaderRef;
    camera = &cameraRef;

    shader->SetMat4(shader->GetUniformLocation("projection"), projection.GetProjection());
    shader->SetMat4(shader->GetUniformLocation("view"), camera->GetViewMatrix());

    InitializeColliders();
}

void Renderer::SetShader(Shader& newShader)
{
    shader = &newShader;
}

Shader& Renderer::GetShader() const
{
    return *shader;
}

Projection& Renderer::GetProjection()
{
    return projection;
}

void Renderer::SetCamera(Camera& newCamera)
{
    camera = &newCamera;
}

Camera& Renderer::GetCamera() const
{
    return *camera;
}

void Renderer::SetShowColliders(bool newVal)
{
    showColliders = newVal;
}

bool Renderer::ShowColliders() const
{
    return showColliders;
}

void Renderer::BeginFrame()
{
    glClearColor(0.20f, 0.15f, 0.18f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->SetMat4(shader->GetUniformLocation("projection"), projection.GetProjection());
    shader->SetMat4(shader->GetUniformLocation("view"), camera->GetViewMatrix());    
}

void Renderer::DrawObject(const Object& object)
{
    shader->SetMat4(shader->GetUniformLocation("model"), object.GetTransform().GetMatrix());
    shader->SetBool(shader->GetUniformLocation("useTexture"), object.IsUsingTexture());
    shader->SetVec4(shader->GetUniformLocation("objectColor"), object.GetColor());
    object.DrawObject();
}

void Renderer::DrawCameraFixedObject(CameraFixedObject& cameraFixedObject, Camera& cameraRef)
{
    cameraFixedObject.SetCamera(cameraRef);
    shader->SetMat4(shader->GetUniformLocation("model"), cameraFixedObject.GetMatrix());
    shader->SetBool(shader->GetUniformLocation("useTexture"), cameraFixedObject.IsUsingTexture());
    shader->SetVec4(shader->GetUniformLocation("objectColor"), cameraFixedObject.GetColor());
    cameraFixedObject.DrawObject();
}

void Renderer::InitializeColliders()
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

void Renderer::DrawCollider(const ICollidable& collidable)
{
    Collider collider = collidable.GetWorldCollider();
    if (collider.colliderShape == ColliderShape::Box)
    {
        glm::mat4 transform{1.0f};
        transform = glm::translate(transform, collider.center);
        transform = glm::scale(transform, collider.halfSize * 2.0f);

        shader->SetMat4(shader->GetUniformLocation("model"), transform);
        shader->SetBool(shader->GetUniformLocation("useTexture"), false);
        shader->SetVec4(shader->GetUniformLocation("objectColor"), RGBAtoVec4(17, 242, 85, 255));

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBindVertexArray(boxColliderVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } 
}

void Renderer::DrawColliders(Scene& scene)
{
    if (showColliders)
    {
        for (const Object& object : scene.GetObjects())
        {
            if (object.IsActive())
            {
                DrawCollider(object);
            }
        }
    }
}

void Renderer::RenderScene(Scene& scene)
{
    BeginFrame();

    for (const Object& object : scene.GetObjects())
    {
        if (object.IsActive())
        {
            DrawObject(object);
        }
    }
    for (CameraFixedObject& cameraFixedObject : scene.GetCameraFixedObjects())
    {
        if (cameraFixedObject.IsActive())
        {
            cameraFixedObject.GetTransform().Translate(glm::vec3{0.0f, 0.0f, -0.05f});
            
            //FIXME: DrawCameraFixedObject(cameraFixedObject, cameraFixedObject.GetCamera());  
            //DrawCameraFixedObject(cameraFixedObject, GetCamera());  
        }  
    }
}