#include "CameraController.h"

#include "Camera.h"

CameraController::CameraController(InputManager& inputManager)
    : inputManager(inputManager)
{

}

void CameraController::SetActive(bool val)
{
    isActive = val;
}

bool CameraController::IsActive() const
{
    return isActive;
}

void CameraController::SetCamera(Camera& newCamera)
{
    camera = &newCamera;
}

Camera& CameraController::GetCamera()
{
    return *camera;
}

const Camera& CameraController::GetCamera() const
{
    return *camera;
}

void CameraController::Update(float deltaTime)
{
    if (isActive)
    {
        HandleMovement(deltaTime);
        HandleRotation();
    }
}

/// <summary>
/// Handle camera movement with WASDQE
/// </summary>
void CameraController::HandleMovement(float deltaTime)
{
    if (inputManager.IsKeyPressed(GLFW_KEY_W))
    {
        glm::vec3 forwardVector = camera->GetForwardVector();
        forwardVector.y = 0;
        forwardVector = glm::normalize(forwardVector);
        camera->Translate(forwardVector * distanceAmount * deltaTime);
    }
    else if (inputManager.IsKeyPressed(GLFW_KEY_S))
    {
        glm::vec3 forwardVector = camera->GetForwardVector();
        forwardVector.y = 0;
        forwardVector = glm::normalize(forwardVector);
        camera->Translate(-forwardVector * distanceAmount * deltaTime);
    }

    if (inputManager.IsKeyPressed(GLFW_KEY_D))
    {
        camera->Translate(camera->GetRightVector() * distanceAmount * deltaTime);
    }
    else if (inputManager.IsKeyPressed(GLFW_KEY_A))
    {
        camera->Translate(-camera->GetRightVector() * distanceAmount * deltaTime);
    }

    if (inputManager.IsKeyPressed(GLFW_KEY_Q))
    {
        camera->Translate(glm::vec3{0.0f, 1.0f, 0.0f} * distanceAmount * deltaTime);
    }
    else if (inputManager.IsKeyPressed(GLFW_KEY_E))
    {
        camera->Translate(glm::vec3{0.0f, -1.0f, 0.0f} * distanceAmount * deltaTime);
    }
}

/// <summary>
/// Handle camera rotation with cursor movement
/// </summary>
void CameraController::HandleRotation()
{
    // if deltaXpos > 0 then the mouse moved right
    // if deltaYpos > 0 then the mouse moved up
    glm::vec2 cursorDeltaPos = inputManager.GetCursorDeltaPos();

    // Handle horizontal rotation
    float rotationAmount = cursorDeltaPos.x * mouseSensitivity;
    camera->RotateRelative(glm::vec3{0.0f, -rotationAmount, 0.0f});

    // Handle vertical rotation
    rotationAmount = cursorDeltaPos.y * mouseSensitivity;
    camera->RotateRelative(glm::vec3{-rotationAmount, 0.0f, 0.0f});
}