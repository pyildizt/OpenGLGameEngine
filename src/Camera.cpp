#include "Camera.h"

#include <iostream>

int Camera::cameraCount = 0;
bool debugCamera{true};

Camera::Camera()
{
    cameraID = ++Camera::cameraCount;
}

int Camera::GetCameraID() const
{
    return cameraID;
}

glm::mat4 Camera::GetViewMatrix() const
{
    //TODO: Reverse these transformations if necessary

    glm::mat4 transform{1.0f}; // identity matrix

    // Do x, y, z rotations in order
    // Quaternions will be implemented later to fix rotation issues
    //transform = glm::rotate(transform, glm::radians(-rotationVector.x), glm::vec3(1.0f, 0.0, 0.0));
    transform = glm::rotate(transform, glm::radians(-rotationVector.y), glm::vec3(0.0f, 1.0, 0.0));
    //transform = glm::rotate(transform, glm::radians(-rotationVector.z), glm::vec3(0.0f, 0.0, 1.0));

    transform = glm::translate(transform, -positionVector);

    return transform;
}

void Camera::RotateRelative(glm::vec3 amount)
{
    rotationVector = rotationVector + amount;
}

void Camera::SetRotation(glm::vec3 newVal)
{
    rotationVector = newVal;
}

glm::vec3 Camera::GetRotationVector() const
{
    if (debugCamera)
    {
        std::cout << "Camera rot. (" << rotationVector.x << ", " << rotationVector.y << ", " << rotationVector.z << ")" << std::endl;
    }

    return rotationVector;
}

void Camera::Translate(glm::vec3 amount)
{
    positionVector = positionVector + amount;
}

void Camera::SetPosition(glm::vec3 newVal)
{
    positionVector = newVal;
}