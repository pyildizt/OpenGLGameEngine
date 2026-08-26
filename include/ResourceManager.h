#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Model.h"
#include "Shader.h"
#include "Texture.h"

#include <string>
#include <unordered_map>

class ResourceManager
{
private:
    std::unordered_map<std::string, Model> models;
    std::unordered_map<std::string, Texture> textures;
    std::unordered_map<std::string, Shader> shaders;

public:
    ResourceManager();

    Model& GetOrLoadModel(const std::string& modelFilename);
    Texture& GetOrLoadTexture(const std::string& textureFilename);
    Shader& GetOrLoadShader(const std::string& shaderName, const std::string& vertexShaderFilepath, const std::string& fragmentShaderFilepath);
};

#endif