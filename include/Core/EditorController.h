#ifndef EDITOR_CONTROLLER_H
#define EDITOR_CONTROLLER_H

#include "Core/InputManager.h"
#include "Scene/SceneNode.h"

enum class EditorMode
{
    Translate,
    Scale,
    Rotate
};

class EditorController
{
private:
    SceneNode* selectedNode{nullptr};
    InputManager& inputManager;

    bool isActive{};

    EditorMode editorMode{EditorMode::Translate};

    float translationSpeed{10.0f};
    float rotationSpeed{10.0f};
    float scaleAmount{1.0f};
    float maxRayDistance{3.0f};

public:
    EditorController(InputManager& inputManager);

    void SetActive(bool newVal);
    bool IsActive() const;

    void SetEditorMode(EditorMode newEditorMode);
    EditorMode GetEditorMode() const;

    void SetSelectedNode(SceneNode* newSceneNode);
    SceneNode* GetSelectedNode();
    const SceneNode* GetSelectedNode() const;

    void Update(float deltaTime);
};

#endif