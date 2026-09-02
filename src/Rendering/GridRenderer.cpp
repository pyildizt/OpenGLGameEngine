#include "Rendering/GridRenderer.h"
#include "Rendering/Shader.h"
#include "Utilities/Utils.h"

#include <vector>

GridRenderer::GridRenderer()
{
    InitializeGrid();
}

void GridRenderer::SetShowGrid(bool newVal)
{
    showGrid = newVal;
}

bool GridRenderer::ShowGrid() const
{
    return showGrid;
}

void GridRenderer::InitializeGrid()
{
    std::vector<glm::vec3> vertices;
    // x axis lines
    for (float z = -gridHalfSize; z <= gridHalfSize; z += gridStepSize)
    {
        vertices.emplace_back(-gridHalfSize, 0.005f, z);
        vertices.emplace_back(gridHalfSize, 0.005f, z);
    }
    // z axis lines
    for (float x = -gridHalfSize; x <= gridHalfSize; x += gridStepSize)
    {
        vertices.emplace_back(x, 0.005f, -gridHalfSize);
        vertices.emplace_back(x, 0.005f, gridHalfSize);
    }
    vertexCount = vertices.size();

    glGenVertexArrays(1, &gridVAO);
    glBindVertexArray(gridVAO);

    glGenBuffers(1, &gridVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);
}

void GridRenderer::DrawGrid(Shader& shader)
{
    if (showGrid)
    {
        glm::mat4 transform{1.0f};
        shader.SetMat4(shader.GetUniformLocation("model"), transform);
        shader.SetBool(shader.GetUniformLocation("useTexture"), false);
        shader.SetVec4(shader.GetUniformLocation("objectColor"), RGBAtoVec4(173, 160, 9, 255));

        glBindVertexArray(gridVAO);
        glDrawArrays(GL_LINES, 0, vertexCount);
    }
}