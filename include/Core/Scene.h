#ifndef SCENE_H
#define SCENE_H

#include "Camera/Camera.h"
#include "Core/ResourceManager.h"
#include "Interfaces/ICollidable.h"
#include "Interfaces/IInteractable.h"
#include "Scene/Door.h"
#include "Scene/GameObject.h"
#include "Scene/RenderObject.h"
#include "Scene/SceneNode.h"

#include <unordered_map>
#include <vector>

class Scene
{
private:
    ResourceManager& resourceManager;

    std::vector<std::unique_ptr<SceneNode>> sceneNodes;

    std::vector<Camera*> cameras; 

    std::vector<ICollidable*> collidables;
    std::vector<IAnimatable*> animatables;
    std::vector<IInteractable*> interactables;

    std::unordered_map<unsigned int, RenderObject*> pickingRenderObjectMap;

    void RegisterNode(SceneNode& nodeRef);
    void UnregisterNode(SceneNode& nodeRef);

public:
    Scene(ResourceManager& resourceManagerRef);

    template<typename T, typename... Args>
    T& AddNode(Args&&... args)
    {
        auto node = std::make_unique<T>(std::forward<Args>(args)...);
        T& nodeRef = *node;
        RegisterNode(nodeRef);
        sceneNodes.push_back(std::move(node));
        return nodeRef;
    }

    SceneNode& AddSceneNode();
    void RemoveSceneNode(SceneNode* node);

    RenderObject& AddRenderObject(Model& modelRef);
    RenderObject& AddRenderObject(const std::string& modelFilename);
    RenderObject& AddRenderObject(const std::string& modelFilename, const std::string& textureFilename);

    GameObject& AddGameObject(Model& modelRef);
    GameObject& AddGameObject(const std::string& modelFilename);
    GameObject& AddGameObject(const std::string& modelFilename, const std::string& textureFilename);

    Door& AddDoor(Model& modelRef, Model& hingeModelRef);
    Door& AddDoor(const std::string& modelFilename, const std::string& hingeModelFilename);

    Camera& AddCamera();

    std::vector<std::unique_ptr<SceneNode>>& GetSceneNodes();

    std::vector<Camera*> GetCameras() const;

    std::vector<ICollidable*> GetCollidables() const;
    std::vector<IAnimatable*> GetAnimatables() const;
    std::vector<IInteractable*> GetInteractables() const;

    std::unordered_map<unsigned int, RenderObject*>& GetPickingRenderObjectMap();
};

#endif