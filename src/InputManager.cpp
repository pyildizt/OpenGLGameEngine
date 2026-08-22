#include "InputManager.h"

InputManager::InputManager(GLFWwindow* windowPtr)
{
    window = windowPtr;
}

void InputManager::EndFrame()
{
    cursorDeltaPos = glm::vec2{0.0f};
}

bool InputManager::IsKeyPressed(int key) const
{
    return (glfwGetKey(window, key) == GLFW_PRESS);
}

void InputManager::SetCursorDeltaPos(float deltaXpos, float deltaYpos)
{
    cursorDeltaPos.x += deltaXpos;
    cursorDeltaPos.y += deltaYpos;
}

glm::vec2 InputManager::GetCursorDeltaPos()
{
    return cursorDeltaPos;
}