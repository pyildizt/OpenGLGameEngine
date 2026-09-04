#include "Core/Scene.h"

Scene::Scene(ResourceManager& resourceManagerRef)
    : resourceManager(resourceManagerRef)
{

}

SceneNode& Scene::AddSceneNode()
{
    return AddNode<SceneNode>();
}

RenderObject& Scene::AddRenderObject(Model& modelRef)
{
    RenderObject& renderObject = AddNode<RenderObject>(modelRef);
    renderObject.SetNodeName("renderObj " + std::to_string(renderObject.GetSceneNodeID()));
    if (!modelRef.HasTexture())
    {
        renderObject.UseTexture(false);
    }
    pickingRenderObjectMap[renderObject.GetPickingID()] = &renderObject;
    return renderObject;
}

RenderObject& Scene::AddRenderObject(const std::string& modelFilename)
{
    Model& modelRef = resourceManager.GetOrLoadModel(modelFilename);
    return AddRenderObject(modelRef);
}

RenderObject& Scene::AddRenderObject(const std::string& modelFilename, const std::string& textureFilename)
{
    Model& modelRef = resourceManager.GetOrLoadModel(modelFilename);
    Texture& textureRef = resourceManager.GetOrLoadTexture(textureFilename);

    modelRef.SetTexture(textureRef);
    return AddRenderObject(modelRef);
}

GameObject& Scene::AddGameObject(Model& modelRef)
{
    GameObject& gameObject = AddNode<GameObject>(modelRef);
    gameObject.SetNodeName("gameObj " + std::to_string(gameObject.GetSceneNodeID()));
    if (!modelRef.HasTexture())
    {
        gameObject.UseTexture(false);
    }
    pickingRenderObjectMap[gameObject.GetPickingID()] = &gameObject;
    return gameObject;
}

GameObject& Scene::AddGameObject(const std::string& modelFilename)
{
    Model& modelRef = resourceManager.GetOrLoadModel(modelFilename);
    return AddGameObject(modelRef);
}

GameObject& Scene::AddGameObject(const std::string& modelFilename, const std::string& textureFilename)
{
    Model& modelRef = resourceManager.GetOrLoadModel(modelFilename);
    Texture& textureRef = resourceManager.GetOrLoadTexture(textureFilename);

    modelRef.SetTexture(textureRef);

    return AddGameObject(modelRef);
}

Camera& Scene::AddCamera()
{
    Camera& camera = AddNode<Camera>();
    camera.SetNodeName("camera " + std::to_string(camera.GetSceneNodeID()));
    return camera;
}

std::vector<std::unique_ptr<SceneNode>>& Scene::GetSceneNodes()
{
    return sceneNodes;
}

std::vector<GameObject*> Scene::GetGameObjects() const
{
    std::vector<GameObject*> gameObjects;
    for (const auto& node : sceneNodes)
    {
        GetNodeGameObjects(*node, gameObjects);
    }
    return gameObjects;
}

void Scene::GetNodeGameObjects(const SceneNode& node, std::vector<GameObject*>& gameObjects) const
{
    if (!node.IsActive())
    {
        return;
    }

    if (const GameObject* gameObject = dynamic_cast<const GameObject*>(&node))
    {
        gameObjects.push_back(const_cast<GameObject*>(gameObject));
    }

    for (const SceneNode* child : node.GetChildren())
    {
        GetNodeGameObjects(*child, gameObjects);
    }
}

std::vector<Camera*> Scene::GetCameras() const
{
    std::vector<Camera*> cameras;
    for (const auto& node : sceneNodes)
    {
        if (const Camera* camera = dynamic_cast<const Camera*>(node.get()))
        {
            GetNodeCameras(*node, cameras);
        }
    }
    return cameras;
}

void Scene::GetNodeCameras(const SceneNode& node, std::vector<Camera*>& cameras) const
{
    if (!node.IsActive())
    {
        return;
    }

    if (const Camera* camera = dynamic_cast<const Camera*>(&node))
    {
        cameras.push_back(const_cast<Camera*>(camera));
    }

    for (const SceneNode* child : node.GetChildren())
    {
        GetNodeCameras(*child, cameras);
    }
}

std::unordered_map<unsigned int, RenderObject*>& Scene::GetPickingRenderObjectMap()
{
    return pickingRenderObjectMap;
}