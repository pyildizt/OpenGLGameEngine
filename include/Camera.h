#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

class Camera 
{
private:
    int cameraID;

    glm::vec3 positionVector{0.0f, 0.0f, -3.0f};
    glm::vec3 rotationVector{0.0f};

public:
    static int cameraCount;

    Camera();

    int GetCameraID() const;

    glm::mat4 GetViewMatrix() const;

    void RotateRelative(glm::vec3 amount);
    void SetRotation(glm::vec3 newVal);

    void Translate(glm::vec3 amount);
    void SetPosition(glm::vec3 newVal);
};

#endif