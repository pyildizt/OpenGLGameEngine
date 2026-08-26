#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "Camera.h"
#include "ICollidable.h"
#include "InputManager.h"

class PlayerController : public ICollidable
{
private:
    InputManager& inputManager;
    Camera playerCamera;
    Collider collider;

    bool isActive{true};

    float distanceAmount{10.0f};
    float mouseSensitivity{0.5f};

    void HandleMovement(float deltaTime);
    void HandleRotation();

public:
    PlayerController(InputManager& inputManager);

    void SetActive(bool newVal);
    bool IsActive() const;

    Camera& GetPlayerCamera();
    const Camera& GetPlayerCamera() const;

    Collider GetWorldCollider() const override;

    void Update(float deltaTime);
};

#endif