#include "Camera.h"

#include "SceneNode.h"

int Camera::cameraCount = 0;
bool debugCamera{};

Camera::Camera()
    : SceneNode()
{
    cameraID = ++Camera::cameraCount;
}

int Camera::GetCameraID() const
{
    return cameraID;
}

void Camera::RotateRelative(glm::vec3 amount)
{
    rotationVector = rotationVector + amount;

    // Clamp vertical rotation
    rotationVector.x = glm::clamp(rotationVector.x, -89.0f, 89.0f);

    GetLocalTransform().SetRotationEuler(rotationVector);
}

glm::vec3 Camera::GetRotationVector() const
{
    return rotationVector;
}

glm::mat4 Camera::GetViewMatrix() const
{
    glm::vec3 positionVector = GetWorldPosition();

    glm::mat4 transform{1.0f}; // identity matrix
    transform = glm::rotate(transform, glm::radians(-rotationVector.x), glm::vec3(1.0f, 0.0, 0.0));
    transform = glm::rotate(transform, glm::radians(-rotationVector.y), glm::vec3(0.0f, 1.0, 0.0));
    transform = glm::translate(transform, -positionVector);

    return transform;
}

void Camera::CalculateCameraVectors()
{
    glm::vec4 forward{0.0f, 0.0f, -1.0f, 0.0f};
    glm::vec4 right{1.0f, 0.0f, 0.0f, 0.0f};
    glm::vec4 up{0.0f, 1.0f, 0.0f, 0.0f};

    // Handle horizontal rotation first (this does not change upVector)
    glm::mat4 horizontalTransform{1.0f};
    horizontalTransform = glm::rotate(horizontalTransform, glm::radians(rotationVector.y), glm::vec3(0.0f, 1.0f, 0.0f));
    
    forward = horizontalTransform * forward;
    right = horizontalTransform * right;

    // Handle vertical rotation on local plane (rightVector is the normal of this plane)
    glm::mat4 verticalTransform{1.0f};
    verticalTransform = glm::rotate(verticalTransform, glm::radians(rotationVector.x), glm::vec3{right});

    forward = verticalTransform * forward;
    up = verticalTransform * up;

    // Normalize vectors
    forwardVector = glm::vec3{glm::normalize(forward)};
    rightVector = glm::vec3{glm::normalize(right)};
    upVector = glm::vec3{glm::normalize(up)};
}

glm::vec3 Camera::GetForwardVector()
{
    CalculateCameraVectors();
    return forwardVector;
}

glm::vec3 Camera::GetRightVector()
{
    CalculateCameraVectors();
    return rightVector;
}

glm::vec3 Camera::GetUpVector()
{
    CalculateCameraVectors();
    return upVector;
}