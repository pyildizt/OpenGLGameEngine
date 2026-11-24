#include "Core/Scene.h"

Scene::Scene(ResourceManager& resourceManagerRef)
    : resourceManager(resourceManagerRef)
{

}

void Scene::RegisterNode(SceneNode& nodeRef)
{
    if (auto* camera = dynamic_cast<Camera*>(&nodeRef))
    {
        cameras.push_back(camera);
    }
    if (auto* collidable = dynamic_cast<ICollidable*>(&nodeRef))
    {
        collidables.push_back(collidable);
    } 
    if (auto* animatable = dynamic_cast<IAnimatable*>(&nodeRef))
    {
        animatables.push_back(animatable);
    }
    if (auto* interactable = dynamic_cast<IInteractable*>(&nodeRef))
    {
        interactables.push_back(interactable);
    }

    for (SceneNode* child : nodeRef.GetChildren())
    {
        RegisterNode(*child);
    }
}

void Scene::UnregisterNode(SceneNode& nodeRef)
{
    if (auto* camera = dynamic_cast<Camera*>(&nodeRef))
    {
        std::erase(cameras, camera);
    }
    if (auto* collidable = dynamic_cast<ICollidable*>(&nodeRef))
    {
        std::erase(collidables, collidable);
    }
    if (auto* animatable = dynamic_cast<IAnimatable*>(&nodeRef))
    {
        std::erase(animatables, animatable);
    }
    if (auto* interactable = dynamic_cast<IInteractable*>(&nodeRef))
    {
        std::erase(interactables, interactable);
    }

    for (SceneNode* child : nodeRef.GetChildren())
    {
        UnregisterNode(*child);
    }
}

SceneNode& Scene::AddSceneNode()
{
    return AddNode<SceneNode>();
}

void Scene::RemoveSceneNode(SceneNode* node)
{
    for (auto it = sceneNodes.begin(); it != sceneNodes.end(); it++)
    {
        if (it->get() == node)
        {
            UnregisterNode(**it); // *it to get unique_ptr, **it to get the actual object
            sceneNodes.erase(it);
            return;
        }
    }
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

Door& Scene::AddDoor(Model& modelRef, Model& hingeModelRef)
{
    Door& door = AddNode<Door>(modelRef, hingeModelRef);
    door.SetNodeName("door " + std::to_string(door.GetSceneNodeID()));
    if (!modelRef.HasTexture())
    {
        door.GetDoorObject().UseTexture(false);
    }
    pickingRenderObjectMap[door.GetDoorHinge().GetPickingID()] = &door.GetDoorHinge();
    pickingRenderObjectMap[door.GetDoorObject().GetPickingID()] = &door.GetDoorObject();
    return door;
}

Door& Scene::AddDoor(const std::string& modelFilename, const std::string& hingeModelFilename)
{
    Model& modelRef = resourceManager.GetOrLoadModel(modelFilename);
    Model& hingeModelRef = resourceManager.GetOrLoadModel(hingeModelFilename);
    return AddDoor(modelRef, hingeModelRef);
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

std::vector<ICollidable*> Scene::GetCollidables() const
{
    return collidables;
}

std::vector<Camera*> Scene::GetCameras() const
{
    return cameras;
}

std::vector<IAnimatable*> Scene::GetAnimatables() const
{
    return animatables;
}

std::vector<IInteractable*> Scene::GetInteractables() const
{
    return interactables;
}

std::unordered_map<unsigned int, RenderObject*>& Scene::GetPickingRenderObjectMap()
{
    return pickingRenderObjectMap;
}