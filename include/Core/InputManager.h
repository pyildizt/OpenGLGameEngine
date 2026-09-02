#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

class InputManager
{
private:
    GLFWwindow* window;

    glm::vec2 cursorPrevPos{1080.0f/2, 720.0f/2};
    glm::vec2 cursorDeltaPos{};

    static void CursorPosCallbackWrapper(GLFWwindow* window, double xpos, double ypos);
    void CursorPosCallback(GLFWwindow* windowPtr, double xpos, double ypos);

public:
    InputManager(GLFWwindow* window);

    void EndFrame();

    bool IsKeyPressed(int key) const;

    glm::vec2 GetCursorDeltaPos();
};

#endif