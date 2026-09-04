#include "Core/EditorController.h"

#include "Scene/SceneNode.h"

EditorController::EditorController(InputManager& inputManager)
    : inputManager(inputManager)
{

}

void EditorController::SetActive(bool val)
{
    isActive = val;
}

bool EditorController::IsActive() const
{
    return isActive;
}

void EditorController::SetEditorMode(EditorMode newEditorMode)
{
    editorMode = newEditorMode;
}

EditorMode EditorController::GetEditorMode() const
{
    return editorMode;
}

void EditorController::SetSelectedNode(SceneNode* newSceneNode)
{
    selectedNode = newSceneNode;
}

SceneNode* EditorController::GetSelectedNode()
{
    return selectedNode;
}

const SceneNode* EditorController::GetSelectedNode() const
{
    return selectedNode;
}

void EditorController::Update(float deltaTime)
{
    if (selectedNode == nullptr)
    {
        return;
    }

    if (inputManager.IsKeyPressed(GLFW_KEY_1))
    {
        SetEditorMode(EditorMode::Translate);
    }
    else if (inputManager.IsKeyPressed(GLFW_KEY_2))
    {
        SetEditorMode(EditorMode::Scale);
    }
    else if (inputManager.IsKeyPressed(GLFW_KEY_3))
    {
        SetEditorMode(EditorMode::Rotate);
    }

    if (GetEditorMode() == EditorMode::Translate)
    {
        // Translate (world) with WASDQE
        if (inputManager.IsKeyPressed(GLFW_KEY_W))
        {
            selectedNode->GetLocalTransform().Translate(glm::vec3{0.0f, 0.0f, -1.0f} * translationSpeed * deltaTime);
        }
        else if (inputManager.IsKeyPressed(GLFW_KEY_S))
        {
            selectedNode->GetLocalTransform().Translate(glm::vec3{0.0f, 0.0f, 1.0f} * translationSpeed * deltaTime);
        }

        if (inputManager.IsKeyPressed(GLFW_KEY_D))
        {
            selectedNode->GetLocalTransform().Translate(glm::vec3{1.0f, 0.0f, 0.0f} * translationSpeed * deltaTime);
        }
        else if (inputManager.IsKeyPressed(GLFW_KEY_A))
        {
            selectedNode->GetLocalTransform().Translate(glm::vec3{-1.0f, 0.0f, 0.0f} * translationSpeed * deltaTime);
        }

        if (inputManager.IsKeyPressed(GLFW_KEY_Q))
        {
            selectedNode->GetLocalTransform().Translate(glm::vec3{0.0f, 1.0f, 0.0f} * translationSpeed * deltaTime);
        }
        else if (inputManager.IsKeyPressed(GLFW_KEY_E))
        {
            selectedNode->GetLocalTransform().Translate(glm::vec3{0.0f, -1.0f, 0.0f} * translationSpeed * deltaTime);
        }
    }
    else if (GetEditorMode() == EditorMode::Scale)
    {
        // Scale with WASDQE
        if (inputManager.IsKeyPressed(GLFW_KEY_W))
        {
            selectedNode->GetLocalTransform().ScaleRelative(glm::vec3{1.0f, 1.0f, 1.0f + scaleAmount * deltaTime});
        }
        else if (inputManager.IsKeyPressed(GLFW_KEY_S))
        {
            selectedNode->GetLocalTransform().ScaleRelative(glm::vec3{1.0f, 1.0f, 1.0f - scaleAmount * deltaTime});
        }

        if (inputManager.IsKeyPressed(GLFW_KEY_D))
        {
            selectedNode->GetLocalTransform().ScaleRelative(glm::vec3{1.0f + scaleAmount * deltaTime, 1.0f, 1.0f});
        }
        else if (inputManager.IsKeyPressed(GLFW_KEY_A))
        {
            selectedNode->GetLocalTransform().ScaleRelative(glm::vec3{1.0f - scaleAmount * deltaTime, 1.0f, 1.0f});
        }

        if (inputManager.IsKeyPressed(GLFW_KEY_Q))
        {
            selectedNode->GetLocalTransform().ScaleRelative(glm::vec3{1.0f, 1.0f + scaleAmount * deltaTime, 1.0f});
        }
        else if (inputManager.IsKeyPressed(GLFW_KEY_E))
        {
            selectedNode->GetLocalTransform().ScaleRelative(glm::vec3{1.0f, 1.0f - scaleAmount * deltaTime, 1.0f});
        }

        // Scale uniform with RT
        if (inputManager.IsKeyPressed(GLFW_KEY_R))
        {
            selectedNode->GetLocalTransform().ScaleRelative(glm::vec3{1.0f + scaleAmount * deltaTime});
        }
        else if (inputManager.IsKeyPressed(GLFW_KEY_T))
        {
            selectedNode->GetLocalTransform().ScaleRelative(glm::vec3{1.0f - scaleAmount * deltaTime});
        }

        // Reset scale with Y
        if (inputManager.IsKeyPressed(GLFW_KEY_Y))
        {
            selectedNode->GetLocalTransform().scaleVector = glm::vec3{1.0f};
        }
    }
    else if (GetEditorMode() == EditorMode::Rotate)
    {
        // Rotate in world xyz axes with WASDQE
        if (inputManager.IsKeyPressed(GLFW_KEY_W))
        {
            selectedNode->GetLocalTransform().RotateRelative(1.0f * rotationSpeed * deltaTime, glm::vec3{0.0f, 0.0f, 1.0f});
        }
        else if (inputManager.IsKeyPressed(GLFW_KEY_S))
        {
            selectedNode->GetLocalTransform().RotateRelative(-1.0f * rotationSpeed * deltaTime, glm::vec3{0.0f, 0.0f, 1.0f});
        }

        if (inputManager.IsKeyPressed(GLFW_KEY_D))
        {
            selectedNode->GetLocalTransform().RotateRelative(1.0f * rotationSpeed * deltaTime, glm::vec3{1.0f, 0.0f, 0.0f});
        }
        else if (inputManager.IsKeyPressed(GLFW_KEY_A))
        {
            selectedNode->GetLocalTransform().RotateRelative(-1.0f * rotationSpeed * deltaTime, glm::vec3{1.0f, 0.0f, 0.0f});
        }

        if (inputManager.IsKeyPressed(GLFW_KEY_Q))
        {
            selectedNode->GetLocalTransform().RotateRelative(1.0f * rotationSpeed * deltaTime, glm::vec3{0.0f, 1.0f, 0.0f});
        }
        else if (inputManager.IsKeyPressed(GLFW_KEY_E))
        {
            selectedNode->GetLocalTransform().RotateRelative(-1.0f * rotationSpeed * deltaTime, glm::vec3{0.0f, 1.0f, 0.0f});
        }
    }
}