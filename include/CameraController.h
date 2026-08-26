#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "Camera.h"
#include "InputManager.h"

class CameraController
{
private:
    Camera* camera{nullptr};
    InputManager& inputManager;

    bool isActive{};

    float distanceAmount{10.0f};
    float mouseSensitivity{0.5f};

    void HandleMovement(float deltaTime);
    void HandleRotation();

public:
    CameraController(InputManager& inputManager);

    void SetActive(bool val);
    bool IsActive() const;

    void SetCamera(Camera& newCamera);
    Camera& GetCamera();
    const Camera& GetCamera() const;

    void Update(float deltaTime);
};

#endif