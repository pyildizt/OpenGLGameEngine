#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "CameraFixedObject.h"
#include "Object.h"
#include "ResourceManager.h"

#include <vector>

class Scene
{
private:
    ResourceManager& resourceManager;

    std::vector<Object> objects;
    std::vector<CameraFixedObject> cameraFixedObjects;
    std::vector<Camera> cameras;

public:
    Scene(ResourceManager& resourceManagerRef);

    Object& AddObject(Model& modelRef);
    Object& AddObject(const std::string& modelFilename);
    Object& AddObject(const std::string& modelFilename, const std::string& textureFilename);

    CameraFixedObject& AddCameraFixedObject(Model& modelRef);
    CameraFixedObject& AddCameraFixedObject(const std::string& modelFilename);
    CameraFixedObject& AddCameraFixedObject(const std::string& modelFilename, const std::string& textureFilename);

    Camera& AddCamera();

    std::vector<Object>& GetObjects();
    std::vector<CameraFixedObject>& GetCameraFixedObjects();
    std::vector<Camera>& GetCameras();
};

#endif