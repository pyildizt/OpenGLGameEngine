#ifndef CAMERA_H
#define CAMERA_H

#include "Scene/SceneNode.h"

#include <glm/gtc/matrix_transform.hpp>

class Camera : public SceneNode
{
private:
    int cameraID;

    glm::vec3 rotationVector{0.0f};

    glm::vec3 forwardVector{0.0f, 0.0f, -1.0f};
    glm::vec3 rightVector{1.0f, 0.0f, 0.0f};
    glm::vec3 upVector{0.0f, 1.0f, 0.0f};

    void CalculateCameraVectors();

public:
    static int cameraCount;

    Camera();

    int GetCameraID() const;

    void RotateRelative(glm::vec3 amount);
    glm::vec3 GetRotationVector() const;

    glm::mat4 GetViewMatrix() const;

    glm::vec3 GetForwardVector();
    glm::vec3 GetRightVector();
    glm::vec3 GetUpVector();
};

#endif