#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Model.h"
#include "Texture.h"

#include <string>
#include <unordered_map>

class ResourceManager
{
private:
    std::unordered_map<std::string, Model> models;
    std::unordered_map<std::string, Texture> textures;

public:
    ResourceManager();

    Model& GetOrLoadModel(const std::string& modelFilename);
    Texture& GetOrLoadTexture(const std::string& textureFilename);
};

#endif