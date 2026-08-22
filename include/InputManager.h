#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

class InputManager
{
private:
    GLFWwindow* window;

    glm::vec2 cursorDeltaPos{};

public:
    InputManager(GLFWwindow* windowPtr);

    void EndFrame();

    bool IsKeyPressed(int key) const;

    void SetCursorDeltaPos(float deltaXpos, float deltaYpos);
    glm::vec2 GetCursorDeltaPos();
};

#endif