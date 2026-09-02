#ifndef GAME_H
#define GAME_H

#include "Camera/CameraController.h"
#include "Core/CollisionSystem.h"
#include "Core/InputManager.h"
#include "Core/PlayerController.h"
#include "Core/ResourceManager.h"
#include "Core/Scene.h"
#include "Rendering/Renderer.h"

#include <vector>

class Game
{
private:
    // Order of members is important for initialization order!
    InputManager inputManager;
    PlayerController playerController;
    CameraController cameraController;
    CollisionSystem collisionSystem;

    ResourceManager resourceManager;
    std::vector<Scene> scenes;
    Scene* currScene{nullptr};

    Renderer renderer;

public:
    Game(GLFWwindow* window);

    InputManager& GetInputManager();
    PlayerController& GetPlayerController();
    CameraController& GetCameraController();
    CollisionSystem& GetCollisionSystem();

    ResourceManager& GetResourceManager();

    Scene& GetCurrScene();

    Renderer& GetRenderer();
};

#endif