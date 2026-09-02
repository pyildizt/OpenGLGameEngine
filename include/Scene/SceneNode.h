#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include "Scene/Transform.h"

class SceneNode
{
private:
    bool isActive{true};

    Transform localTransform;

    SceneNode* parent{nullptr};
    std::vector<SceneNode*> children;

    void AddChild(SceneNode& child);
    void RemoveChild(SceneNode& child);

public:
    SceneNode();
    virtual ~SceneNode() = default;

    void SetActive(bool val);
    bool IsActive() const;

    Transform& GetLocalTransform();
    const Transform& GetLocalTransform() const;

    glm::vec3 GetWorldPosition() const;
    glm::mat4 GetWorldMatrix() const;

    void SetParent(SceneNode* newParent);
    SceneNode* GetParent() const;
    
    const std::vector<SceneNode*>& GetChildren() const;
};

#endif