#include "ResourceManager.h"

#include <utility>

ResourceManager::ResourceManager()
{
    models.reserve(10);
    textures.reserve(10);
}

Model& ResourceManager::GetOrLoadModel(const std::string& modelFilename)
{
    auto pair = models.try_emplace(modelFilename, modelFilename);
    return pair.first->second; 
}

Texture& ResourceManager::GetOrLoadTexture(const std::string& textureFilename)
{
    auto pair = textures.try_emplace(textureFilename, textureFilename);
    return pair.first->second; 
}

/*
Model& ResourceManager::TryAddModel(const std::string& modelFilename)
{
    auto pair = models.try_emplace(modelFilename, modelFilename);
    return pair.first->second;
    if (pair.second) 
    {
        // if model was emplaced (not already in map), emplace and return it)
        return pair.first->second;
    }
    // if model was already in models map return that
    return models.at(modelFilename);    
}

Model& ResourceManager::GetOrLoadModel(const std::string& modelFilename)
{
    auto iterator = models.find(modelFilename); 
    if (iterator != models.end()) 
    {
        // if model found in models map return it
        return iterator->second;
    }
    // if model was not already in models map, then add and return it
    return TryAddModel(modelFilename);
}
*/