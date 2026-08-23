#include "Scene.h"

Scene::Scene(ResourceManager& resourceManagerRef)
    : resourceManager(resourceManagerRef)
{
    objects.reserve(10);
    cameraFixedObjects.reserve(10);
    cameras.reserve(10);
}

Object& Scene::AddObject(Model& modelRef)
{
    objects.emplace_back(modelRef);
    return objects.back();
}

Object& Scene::AddObject(const std::string& modelFilename)
{
    Model& modelRef = resourceManager.GetOrLoadModel(modelFilename);
    return AddObject(modelRef);
}

Object& Scene::AddObject(const std::string& modelFilename, const std::string& textureFilename)
{
    Model& modelRef = resourceManager.GetOrLoadModel(modelFilename);
    Texture& textureRef = resourceManager.GetOrLoadTexture(textureFilename);

    modelRef.SetTexture(textureRef);

    return AddObject(modelRef);
}

CameraFixedObject& Scene::AddCameraFixedObject(Model& modelRef)
{
    cameraFixedObjects.emplace_back(modelRef);
    return cameraFixedObjects.back();
}

CameraFixedObject& Scene::AddCameraFixedObject(const std::string& modelFilename)
{
    Model& modelRef = resourceManager.GetOrLoadModel(modelFilename);
    return AddCameraFixedObject(modelRef);
}

CameraFixedObject& Scene::AddCameraFixedObject(const std::string& modelFilename, const std::string& textureFilename)
{
    Model& modelRef = resourceManager.GetOrLoadModel(modelFilename);
    Texture& textureRef = resourceManager.GetOrLoadTexture(textureFilename);

    modelRef.SetTexture(textureRef);
    
    return AddCameraFixedObject(modelRef);
}

Camera& Scene::AddCamera()
{
    cameras.emplace_back();
    return cameras.back();
}

std::vector<Object>& Scene::GetObjects()
{
    return objects;
}

std::vector<CameraFixedObject>& Scene::GetCameraFixedObjects()
{
    return cameraFixedObjects;
}

std::vector<Camera>& Scene::GetCameras()
{
    return cameras;
}