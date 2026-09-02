#ifndef GRID_RENDERER_H
#define GRID_RENDERER_H

#include "Rendering/Shader.h"

class GridRenderer
{
private:
    bool showGrid{};

    GLuint gridVAO{};
    GLuint gridVBO{};

    float gridHalfSize{30.0f};
    float gridStepSize{2.0f};

    int vertexCount{};

public:
    GridRenderer();

    void InitializeGrid();

    void SetShowGrid(bool newVal);
    bool ShowGrid() const;

    void DrawGrid(Shader& shader);
};

#endif