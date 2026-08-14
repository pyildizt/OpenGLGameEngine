#include "Projection.h"

/// <summary>
/// Create perspective projection by default
/// </summary>
Projection::Projection()
{
    projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}

void Projection::SetProjection(glm::mat4 newProjection)
{
    projectionMatrix = newProjection;
}

glm::mat4 Projection::GetProjection() const
{
    return projectionMatrix;
}