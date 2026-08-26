#include "InputManager.h"

InputManager::InputManager(GLFWwindow* window)
    : window(window)
{
    glfwSetWindowUserPointer(window, this);

    glfwSetCursorPosCallback(window, CursorPosCallbackWrapper);
}

void InputManager::EndFrame()
{
    cursorDeltaPos = glm::vec2{0.0f};
}

bool InputManager::IsKeyPressed(int key) const
{
    return (glfwGetKey(window, key) == GLFW_PRESS);
}

glm::vec2 InputManager::GetCursorDeltaPos()
{
    return cursorDeltaPos;
}

void InputManager::CursorPosCallbackWrapper(GLFWwindow* window, double xpos, double ypos)
{
    // Needed because apparently GLFW does not accept non-static function
    auto* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    inputManager->CursorPosCallback(window, xpos, ypos);
}

void InputManager::CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    // Calculate current xpos and ypos difference from previous frame
    double deltaXpos = xpos - cursorPrevPos.x;
    double deltaYpos = ypos - cursorPrevPos.y;

    cursorDeltaPos.x += deltaXpos;
    cursorDeltaPos.y += deltaYpos;

    // Update prev xpos and ypos
    cursorPrevPos.x = xpos;
    cursorPrevPos.y = ypos;
}