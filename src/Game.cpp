#include "Game.h"

#include "CameraController.h"
#include "CollisionSystem.h"
#include "InputManager.h"
#include "PlayerController.h"
#include "Renderer.h"
#include "ResourceManager.h"

Game::Game(GLFWwindow* window)
    : inputManager(window), 
      playerController(inputManager), cameraController(inputManager), collisionSystem(),
      resourceManager(),
      renderer()
{
    // Create main scene
    scenes.emplace_back(resourceManager);
    currScene = &scenes.back();

    // Create main shader and initialize main renderer
    Shader& mainShader = resourceManager.GetOrLoadShader(
        "main",
        "shaders/vertex.glsl",
        "shaders/fragment.glsl"
    );
    renderer.InitializeRenderer(mainShader, playerController.GetPlayerCamera());
}

InputManager& Game::GetInputManager()
{
    return inputManager;
}

PlayerController& Game::GetPlayerController()
{
    return playerController;
}

CameraController& Game::GetCameraController()
{
    return cameraController;
}

CollisionSystem& Game::GetCollisionSystem()
{
    return collisionSystem;
}

ResourceManager& Game::GetResourceManager()
{
    return resourceManager;
}

Scene& Game::GetCurrScene()
{
    return *currScene;
}

Renderer& Game::GetRenderer()
{
    return renderer;
}