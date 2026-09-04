#include "Scene/SceneNode.h"

#include <algorithm>

int SceneNode::sceneNodeCount = 0;

SceneNode::SceneNode()
{
    nodeID = sceneNodeCount++;
    nodeName = "node " + std::to_string(nodeID);
    isActive = true;
    localTransform = Transform{}; 
}

int SceneNode::GetSceneNodeID() const
{
    return nodeID;
}

void SceneNode::SetActive(bool newVal)
{
    isActive = newVal;
}

bool SceneNode::IsActive() const
{
    return isActive;
}

void SceneNode::SetNodeName(const std::string& newName)
{
    nodeName = newName;
}

void SceneNode::AddNodeName(const std::string& appendName)
{
    nodeName = nodeName + ": " + appendName;
}

const std::string& SceneNode::GetNodeName() const
{
    return nodeName;
}

Transform& SceneNode::GetLocalTransform()
{
    return localTransform;
}

const Transform& SceneNode::GetLocalTransform() const
{
    return localTransform;
}

/// <summary>
/// Handles both setParent and add/remove children.
/// So always call SetParent from child, instead of AddChild from parent.
/// </summary>
void SceneNode::SetParent(SceneNode* newParent)
{
    // Remove from current parent
    if (parent != nullptr)
    {
        parent->RemoveChild(*this);
    }

    parent = newParent;

    // Add to new parent
    if (parent != nullptr)
    {
        parent->AddChild(*this);
    }
}

SceneNode* SceneNode::GetParent() const
{
    return parent;
}

void SceneNode::AddChild(SceneNode& child)
{
    children.push_back(&child);
}

void SceneNode::RemoveChild(SceneNode& child)
{
    auto iterator = std::find(children.begin(), children.end(), &child);

    if (iterator != children.end())
    {
        children.erase(iterator);
    }
}

const std::vector<SceneNode*>& SceneNode::GetChildren() const
{
    return children;
}

glm::vec3 SceneNode::GetWorldPosition() const
{
    glm::mat4 worldMatrix = GetWorldMatrix();
    return glm::vec3(worldMatrix[3]);
}

glm::mat4 SceneNode::GetWorldMatrix() const
{
    if (parent != nullptr)
    {
        return parent->GetWorldMatrix() * localTransform.GetMatrix();
    }

    return localTransform.GetMatrix();
}