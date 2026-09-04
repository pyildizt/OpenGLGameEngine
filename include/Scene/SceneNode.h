#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include "Scene/Transform.h"

class SceneNode
{
private:
    unsigned int nodeID;

    bool isActive{true};

    std::string nodeName{};

    Transform localTransform;

    SceneNode* parent{nullptr};
    std::vector<SceneNode*> children;

    void AddChild(SceneNode& child);
    void RemoveChild(SceneNode& child);

public:
    static int sceneNodeCount;

    SceneNode();
    virtual ~SceneNode() = default;

    int GetSceneNodeID() const;

    void SetActive(bool val);
    bool IsActive() const;

    void SetNodeName(const std::string& newName);
    void AddNodeName(const std::string& appendName);
    const std::string& GetNodeName() const;

    Transform& GetLocalTransform();
    const Transform& GetLocalTransform() const;

    glm::vec3 GetWorldPosition() const;
    glm::mat4 GetWorldMatrix() const;

    void SetParent(SceneNode* newParent);
    SceneNode* GetParent() const;
    
    const std::vector<SceneNode*>& GetChildren() const;
};

#endif