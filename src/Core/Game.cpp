#include "Core/Game.h"

#include "Camera/CameraController.h"
#include "Core/CollisionSystem.h"
#include "Core/EditorController.h"
#include "Core/InputManager.h"
#include "Core/PlayerController.h"
#include "Core/ResourceManager.h"
#include "Rendering/Renderer.h"

Game::Game(GLFWwindow* window)
    : inputManager(window), 
      playerController(inputManager), cameraController(inputManager), editorController(inputManager), collisionSystem(),
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

    // Create picking shader
    Shader& pickingShader = resourceManager.GetOrLoadShader(
        "picking",
        "shaders/vertex_picking.glsl",
        "shaders/fragment_picking.glsl"
    );
    renderer.GetPickingRenderer().SetShader(pickingShader);
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

EditorController& Game::GetEditorController()
{
    return editorController;
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

void Game::SetInputMode(InputMode newInputMode)
{
    inputMode = newInputMode;
}

InputMode Game::GetInputMode() const
{
    return inputMode;
}