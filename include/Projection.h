#ifndef PROJECTION_H
#define PROJECTION_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Projection
{
private:
    glm::mat4 projectionMatrix{1.0f};

public:
    Projection();

    void SetProjection(glm::mat4 newProjection);
    glm::mat4 GetProjection() const;
};

#endif