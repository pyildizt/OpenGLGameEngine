#ifndef GAME_H
#define GAME_H

#include "CameraController.h"
#include "CollisionSystem.h"
#include "InputManager.h"
#include "PlayerController.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"

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