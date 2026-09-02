#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

struct Transform
{
    glm::vec3 scaleVector{1.0f, 1.0f, 1.0f};
    glm::quat rotationQuaternion{1.0f, 0.0f, 0.0f, 0.0f};
    glm::vec3 positionVector{0.0f, 0.0f, 0.0f};

    glm::mat4 GetMatrix() const;

    void ScaleRelative(glm::vec3 amount);
    void RotateRelative(glm::vec3 amount);
    void RotateRelative(float amount, glm::vec3 axis);
    void Translate(glm::vec3 amount);

    void SetRotationEuler(glm::vec3 rotationVector);
    glm::vec3 GetRotationEuler() const;
};

#endif