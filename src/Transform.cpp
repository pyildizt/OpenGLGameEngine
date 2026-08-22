#include "Transform.h"

#include <iostream>

bool debugTransform{};

glm::mat4 Transform::GetMatrix() const
{
    glm::mat4 transform{1.0f}; // identity matrix

    transform = glm::translate(transform, positionVector);

    // Do x, y, z rotations in order
    // Quaternions will be implemented later to fix rotation issues
    transform = glm::rotate(transform, glm::radians(rotationVector.x), glm::vec3(1.0f, 0.0, 0.0));
    transform = glm::rotate(transform, glm::radians(rotationVector.y), glm::vec3(0.0f, 1.0, 0.0));
    transform = glm::rotate(transform, glm::radians(rotationVector.z), glm::vec3(0.0f, 0.0, 1.0));

    transform = glm::scale(transform, scaleVector);

    if (debugTransform)
    {
        std::cout << "Transformation matrix consist of:" << std::endl;
        std::cout << "scale (" << scaleVector.x << ", " << scaleVector.y << ", " << scaleVector.z << ")" << std::endl;
        std::cout << "rot.  (" << rotationVector.x << ", " << rotationVector.y << ", " << rotationVector.z << ")" << std::endl;
        std::cout << "pos.  (" << positionVector.x << ", " << positionVector.y << ", " << positionVector.z << ")" << std::endl;
    }

    return transform;
}

void Transform::ScaleRelative(glm::vec3 amount)
{
    scaleVector = scaleVector * amount;
}

void Transform::RotateRelative(glm::vec3 amount)
{
    rotationVector = rotationVector + amount;
}

void Transform::Translate(glm::vec3 amount)
{
    positionVector = positionVector + amount;
}