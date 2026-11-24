#include "Core/Game.h"

#include "Camera/CameraController.h"
#include "Core/AnimationSystem.h"
#include "Core/CollisionSystem.h"
#include "Core/EditorController.h"
#include "Core/InputManager.h"
#include "Core/InteractionSystem.h"
#include "Core/PlayerController.h"
#include "Core/ResourceManager.h"
#include "Rendering/Renderer.h"

Game::Game(GLFWwindow* window)
    : inputManager(window), 
      playerController(inputManager), cameraController(inputManager), editorController(inputManager), 
      collisionSystem(), animationSystem(), interactionSystem(),
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

void Game::Update(float deltaTime)
{
    // Handle input
    playerController.Update(deltaTime);
    cameraController.Update(deltaTime);
    editorController.Update(deltaTime);

    // Handle animations
    animationSystem.Update(GetCurrScene(), deltaTime);

    // Check object collisions with player
    collisionSystem.Update(playerController, GetCurrScene());

    // Check player interactions
    interactionSystem.Update(playerController, GetCurrScene(), inputManager);

    inputManager.EndFrame();
}

void Game::Render()
{
    // Render scene
    renderer.RenderScene(GetCurrScene());

    // Render player collider
    renderer.GetColliderRenderer().DrawCollider(playerController, renderer.GetShader());
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

AnimationSystem& Game::GetAnimationSystem()
{
    return animationSystem;
}

InteractionSystem& Game::GetInteractionSystem()
{
    return interactionSystem;
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