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
    void SetScale(glm::vec3 newVal);

    void RotateRelative(glm::vec3 amount);
    void SetRotation(glm::vec3 newVal);

    void RotateRelativeX(float amount);
    void SetRotationX(float newVal);

    void RotateRelativeY(float amount);
    void SetRotationY(float newVal);

    void RotateRelativeZ(float amount);
    void SetRotationZ(float newVal);

    void Translate(glm::vec3 amount);
    void SetPosition(glm::vec3 newVal);

    void SetTransformValues(glm::vec3 scaleVal, glm::vec3 rotationVal, glm::vec3 positionVal);
};

#endif