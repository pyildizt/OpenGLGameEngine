#include "PlayerController.h"

#include "Camera.h"

PlayerController::PlayerController(InputManager& inputManagerRef)
    : inputManager(inputManagerRef), playerCamera()
{

}

Camera& PlayerController::GetPlayerCamera()
{
    return playerCamera;
}

void PlayerController::Update(float deltaTime)
{
    HandleMovement(deltaTime);
    HandleRotation();
}

/// <summary>
/// Handle camera movement with WASD for FPS style camera relative to delta time
/// </summary>
void PlayerController::HandleMovement(float deltaTime)
{
    if (inputManager.IsKeyPressed(GLFW_KEY_W))
    {
        glm::vec3 forwardVector = playerCamera.GetForwardVector();
        forwardVector.y = 0;
        forwardVector = glm::normalize(forwardVector);
        playerCamera.Translate(forwardVector * distanceAmount * deltaTime);

        // float y = playerCamera.GetRotationVector().y;
        // float x = -sin(glm::radians(y)); float z = -cos(glm::radians(y));
        // playerCamera.Translate(glm::vec3{x, 0.0f, z} * distanceAmount * deltaTime);
    }
    else if (inputManager.IsKeyPressed(GLFW_KEY_S))
    {
        glm::vec3 forwardVector = playerCamera.GetForwardVector();
        forwardVector.y = 0;
        forwardVector = glm::normalize(forwardVector);
        playerCamera.Translate(-forwardVector * distanceAmount * deltaTime);
    }

    if (inputManager.IsKeyPressed(GLFW_KEY_D))
    {
        playerCamera.Translate(playerCamera.GetRightVector() * distanceAmount * deltaTime);

        // float y = playerCamera.GetRotationVector().y;
        // float x = cos(glm::radians(y)); float z = -sin(glm::radians(y));
        // playerCamera.Translate(glm::vec3{x, 0.0f, z} * distanceAmount * deltaTime);
    }
    else if (inputManager.IsKeyPressed(GLFW_KEY_A))
    {
        playerCamera.Translate(-playerCamera.GetRightVector() * distanceAmount * deltaTime);
    }
}

/// <summary>
/// Handle camera rotation with cursor movement for FPS style camera
/// </summary>
void PlayerController::HandleRotation()
{
    // if deltaXpos > 0 then the mouse moved right
    // if deltaYpos > 0 then the mouse moved up
    glm::vec2 cursorDeltaPos = inputManager.GetCursorDeltaPos();

    // Handle horizontal rotation
    float rotationAmount = cursorDeltaPos.x * mouseSensitivity;
    playerCamera.RotateRelative(glm::vec3{0.0f, -rotationAmount, 0.0f});

    // Handle vertical rotation
    rotationAmount = cursorDeltaPos.y * mouseSensitivity;
    playerCamera.RotateRelative(glm::vec3{-rotationAmount, 0.0f, 0.0f});
}