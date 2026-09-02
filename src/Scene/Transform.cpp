#include "Scene/Transform.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <iostream>

bool debugTransform{};

glm::mat4 Transform::GetMatrix() const
{
    glm::mat4 transform{1.0f}; // identity matrix

    transform = glm::translate(transform, positionVector);
    transform *= glm::toMat4(rotationQuaternion);
    transform = glm::scale(transform, scaleVector);

    if (debugTransform)
    {
        glm::vec3 rotationVector = GetRotationEuler();
        
        std::cout << "Transformation matrix consist of:" << std::endl;
        std::cout << "scale (" << scaleVector.x << ", " << scaleVector.y << ", " << scaleVector.z << ")" << std::endl;
        //std::cout << "rot.  (" << rotationQuaternion.w << ", " << rotationQuaternion.x << ", " << rotationQuaternion.y << ", " << rotationQuaternion.z << ")" << std::endl;
        std::cout << "rot.  (" << rotationVector.x << ", " << rotationVector.y << ", " << rotationVector.z << ")" << std::endl;
        std::cout << "pos.  (" << positionVector.x << ", " << positionVector.y << ", " << positionVector.z << ")" << std::endl;
    }

    return transform;
}

void Transform::ScaleRelative(glm::vec3 amount)
{
    scaleVector = scaleVector * amount;
}

/// <summary>
/// Given amount=(x, y, z), rotate around each axis(x, y, z) by the given amount, i.e. rotate around the x-axis by amount.x
/// </summary>
void Transform::RotateRelative(glm::vec3 amount)
{
    glm::quat rotationX = glm::angleAxis(glm::radians(amount.x), glm::vec3{1.0f, 0.0f, 0.0f});
    glm::quat rotationY = glm::angleAxis(glm::radians(amount.y), glm::vec3{0.0f, 1.0f, 0.0f});
    glm::quat rotationZ = glm::angleAxis(glm::radians(amount.z), glm::vec3{0.0f, 0.0f, 1.0f});

    rotationQuaternion = rotationZ * rotationY * rotationX * rotationQuaternion;
}

/// <summary>
/// Rotate around the given axis by given amount
/// </summary>
void Transform::RotateRelative(float amount, glm::vec3 axis)
{
    glm::quat rotation = glm::angleAxis(glm::radians(amount), glm::normalize(axis));

    rotationQuaternion = rotation * rotationQuaternion;
}

void Transform::Translate(glm::vec3 amount)
{
    positionVector = positionVector + amount;
}

void Transform::SetRotationEuler(glm::vec3 rotationVector)
{
    glm::quat rotationX = glm::angleAxis(glm::radians(rotationVector.x), glm::vec3{1.0f, 0.0f, 0.0f});
    glm::quat rotationY = glm::angleAxis(glm::radians(rotationVector.y), glm::vec3{0.0f, 1.0f, 0.0f});
    glm::quat rotationZ = glm::angleAxis(glm::radians(rotationVector.z), glm::vec3{0.0f, 0.0f, 1.0f});

    rotationQuaternion = rotationZ * rotationY * rotationX;
}

glm::vec3 Transform::GetRotationEuler() const
{
    return glm::degrees(glm::eulerAngles(rotationQuaternion));
}