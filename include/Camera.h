#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

class Camera 
{
private:
    int cameraID;

    glm::vec3 positionVector{0.0f, 2.0f, 3.0f};
    glm::vec3 rotationVector{0.0f};

    glm::vec3 forwardVector{0.0f, 0.0f, -1.0f};
    glm::vec3 rightVector{1.0f, 0.0f, 0.0f};
    glm::vec3 upVector{0.0f, 1.0f, 0.0f};

    void CalculateCameraVectors();

public:
    static int cameraCount;

    Camera();

    int GetCameraID() const;

    glm::mat4 GetViewMatrix() const;

    void RotateRelative(glm::vec3 amount);
    void SetRotation(glm::vec3 newVal);
    glm::vec3 GetRotationVector() const;

    void Translate(glm::vec3 amount);
    void SetPosition(glm::vec3 newVal);
    glm::vec3 GetPositionVector() const;

    glm::vec3 GetForwardVector();
    glm::vec3 GetRightVector();
    glm::vec3 GetUpVector();
};

#endif