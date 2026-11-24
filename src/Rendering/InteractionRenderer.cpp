#include "Rendering/InteractionRenderer.h"

#include "Interfaces/IInteractable.h"
#include "Rendering/Shader.h"
#include "Utilities/Utils.h"

InteractionRenderer::InteractionRenderer()
{
    InitializeInteractionSpheres();
}

void InteractionRenderer::SetShowInteractionSpheres(bool newVal)
{
    showInteractionSpheres = newVal;
}

bool InteractionRenderer::ShowInteractionSpheres() const
{
    return showInteractionSpheres;
}

void InteractionRenderer::InitializeInteractionSpheres()
{
    // Sphere vertices and indices
    std::vector<GLfloat> sphereVertices;
    std::vector<GLuint> sphereIndices;

    // Generate vertices
    for (int ring = 0; ring <= sphereRings; ring++)
    {
        float theta = glm::pi<float>() * ring / sphereRings;

        for (int segment = 0; segment <= sphereSegments; segment++)
        {
            float phi = 2.0f * glm::pi<float>() * segment / sphereSegments;

            float x = std::cos(phi) * std::sin(theta);
            float y = std::cos(theta);
            float z = std::sin(phi) * std::sin(theta);

            sphereVertices.push_back(x);
            sphereVertices.push_back(y);
            sphereVertices.push_back(z);
        }
    }

    // Generate horizontal ring lines and vertical meridian lines
    for (int ring = 0; ring <= sphereRings; ring++)
    {
        for (int segment = 0; segment <= sphereSegments; segment++)
        {
            int current = ring * (sphereSegments + 1) + segment;

            // Horizontal line: connect to the next segment
            if (ring > 0 && ring < sphereRings && segment < sphereSegments)
            {
                sphereIndices.push_back(current);
                sphereIndices.push_back(current + 1);
            }

            // Vertical line: connect to the next ring
            if (ring < sphereRings)
            {
                sphereIndices.push_back(current);
                sphereIndices.push_back(current + sphereSegments + 1);
            }
        }
    }

    sphereIndexCount = static_cast<int>(sphereIndices.size());

    // Create and bind VAO, VBOs and EBO
    glGenVertexArrays(1, &sphereVAO);
    glBindVertexArray(sphereVAO);

    glGenBuffers(1, &sphereVBO);
    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(GLfloat), sphereVertices.data(), GL_STATIC_DRAW);
  
    glGenBuffers(1, &sphereEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(GLuint), sphereIndices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
}

void InteractionRenderer::DrawInteractionSphere(const IInteractable& interactable, Shader& shader)
{
    if (showInteractionSpheres)
    {
        InteractionSphere interactionSphere = interactable.GetWorldInteractionSphere();

        glm::mat4 transform{1.0f};
        transform = glm::translate(transform, interactionSphere.center);
        transform = glm::scale(transform, glm::vec3(interactionSphere.radius));

        shader.SetMat4(shader.GetUniformLocation("model"), transform);
        shader.SetBool(shader.GetUniformLocation("useTexture"), false);
        shader.SetVec4(shader.GetUniformLocation("objectColor"), RGBAtoVec4(235, 52, 180, 255));

        glBindVertexArray(sphereVAO);
        glDrawElements(GL_LINES, sphereIndexCount, GL_UNSIGNED_INT, 0);
    }
}

void InteractionRenderer::DrawInteractionSpheres(Scene& scene, Shader& shader)
{
    if (showInteractionSpheres)
    {
        for (const IInteractable* interactable : scene.GetInteractables())
        {
            DrawInteractionSphere(*interactable, shader);
        }
    }
}