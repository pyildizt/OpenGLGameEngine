#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

struct Transform
{
    glm::vec3 scaleVector{1.0f, 1.0f, 1.0f};
    //glm::quat rotation; TODO: Implement quaternions!
    glm::vec3 rotationVector{0.0f, 0.0f, 0.0f};
    glm::vec3 positionVector{0.0f, 0.0f, 0.0f};

    glm::mat4 GetMatrix() const;

    void ScaleRelative(glm::vec3 amount);
    void RotateRelative(glm::vec3 amount);
    void Translate(glm::vec3 amount);
};

#endif