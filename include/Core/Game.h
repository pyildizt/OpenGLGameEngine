#ifndef GAME_H
#define GAME_H

#include "Camera/CameraController.h"
#include "Core/CollisionSystem.h"
#include "Core/EditorController.h"
#include "Core/InputManager.h"
#include "Core/PlayerController.h"
#include "Core/ResourceManager.h"
#include "Core/Scene.h"
#include "Rendering/Renderer.h"

#include <vector>

enum class InputMode
{
    Game,
    Editor
};

class Game
{
private:
    // Order of members is important for initialization order!
    InputManager inputManager;
    PlayerController playerController;
    CameraController cameraController;
    EditorController editorController;
    CollisionSystem collisionSystem;

    ResourceManager resourceManager;
    std::vector<Scene> scenes;
    Scene* currScene{nullptr};

    Renderer renderer;

    InputMode inputMode{InputMode::Game};

public:
    Game(GLFWwindow* window);

    InputManager& GetInputManager();
    PlayerController& GetPlayerController();
    CameraController& GetCameraController();
    EditorController& GetEditorController();
    CollisionSystem& GetCollisionSystem();

    ResourceManager& GetResourceManager();

    Scene& GetCurrScene();

    Renderer& GetRenderer();

    void SetInputMode(InputMode newInputMode);
    InputMode GetInputMode() const;
};

#endif