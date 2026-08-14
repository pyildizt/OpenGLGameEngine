#include "Transform.h"

glm::mat4 Transform::GetMatrix() const
{
    glm::mat4 transform{1.0f}; // identity matrix
    
    transform = glm::scale(transform, scaleVector);

    // Do x, y, z rotations in order
    // Quaternions will be implemented later to fix rotation issues
    transform = glm::rotate(transform, glm::radians(rotationVector.x), glm::vec3(1.0f, 0.0, 0.0));
    transform = glm::rotate(transform, glm::radians(rotationVector.y), glm::vec3(0.0f, 1.0, 0.0));
    transform = glm::rotate(transform, glm::radians(rotationVector.z), glm::vec3(0.0f, 0.0, 1.0));

    transform = glm::translate(transform, positionVector);

    return transform;
}

void Transform::ScaleRelative(glm::vec3 amount)
{
    scaleVector = scaleVector * amount;
}

void Transform::SetScale(glm::vec3 newVal)
{
    scaleVector = newVal;
}

void Transform::RotateRelative(glm::vec3 amount)
{
    rotationVector = rotationVector + amount;
}

void Transform::SetRotation(glm::vec3 newVal)
{
    rotationVector = newVal;
}

void Transform::RotateRelativeX(float amount)
{
    rotationVector.x += amount;
}

void Transform::SetRotationX(float newVal)
{
    rotationVector.x = newVal;
}

void Transform::RotateRelativeY(float amount)
{
    rotationVector.y += amount;
}

void Transform::SetRotationY(float newVal)
{
    rotationVector.y = newVal;
}

void Transform::RotateRelativeZ(float amount)
{
    rotationVector.z += amount;
}

void Transform::SetRotationZ(float newVal)
{
    rotationVector.z = newVal;
}

void Transform::Translate(glm::vec3 amount)
{
    positionVector = positionVector + amount;
}

void Transform::SetPosition(glm::vec3 newVal)
{
    positionVector = newVal;
}

void Transform::SetTransformValues(glm::vec3 scaleVal, glm::vec3 rotationVal, glm::vec3 positionVal)
{
    SetScale(scaleVal);
    SetRotation(rotationVal);
    SetPosition(positionVal);
}