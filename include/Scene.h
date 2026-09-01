#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "CameraFixedObject.h"
#include "GameObject.h"
#include "ResourceManager.h"

#include <vector>

class Scene
{
private:
    ResourceManager& resourceManager;

    std::vector<std::unique_ptr<SceneNode>> sceneNodes;

    std::vector<CameraFixedObject> cameraFixedObjects;

public:
    Scene(ResourceManager& resourceManagerRef);

    template<typename T, typename... Args>
    T& AddNode(Args&&... args)
    {
        auto node = std::make_unique<T>(std::forward<Args>(args)...);
        T& result = *node;
        sceneNodes.push_back(std::move(node));
        return result;
    }

    GameObject& AddGameObject(Model& modelRef);
    GameObject& AddGameObject(const std::string& modelFilename);
    GameObject& AddGameObject(const std::string& modelFilename, const std::string& textureFilename);

    CameraFixedObject& AddCameraFixedObject(Model& modelRef);
    CameraFixedObject& AddCameraFixedObject(const std::string& modelFilename);
    CameraFixedObject& AddCameraFixedObject(const std::string& modelFilename, const std::string& textureFilename);

    Camera& AddCamera();

    std::vector<std::unique_ptr<SceneNode>>& GetSceneNodes();

    std::vector<GameObject*> GetGameObjects() const;
    void GetNodeGameObjects(const SceneNode& node, std::vector<GameObject*>& gameObjects) const;

    std::vector<Camera*> GetCameras() const;

    std::vector<CameraFixedObject>& GetCameraFixedObjects();
};

#endif