#include "Model.h"

#include <iostream>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

Model::Model(const std::string& modelFilename)
{
    if(LoadModelFromObj(modelFilename))
    {
        InitializeModel();
    }
    texture = nullptr;
}

void Model::SetTexture(Texture& newTexture)
{
    texture = &newTexture;
}

Texture* Model::GetTexture()
{
    return texture;
}

bool Model::LoadModelFromObj(const std::string& modelFilename)
{
    tinyobj::ObjReader objReader;
    if (!objReader.ParseFromFile(modelFilename))
    {
        std::cout << "ERROR::MODEL::LOADING MODEL FAILED\n" << std::endl;
        return false;
    }

    auto& attrib = objReader.GetAttrib();
    auto& shapes = objReader.GetShapes();

    vertices = attrib.vertices;
    normals = attrib.normals;
    texcoords = attrib.texcoords;
    for (const auto& index : shapes[0].mesh.indices)
    {
        indices.push_back(index.vertex_index);
    }
    return true;
}

void Model::InitializeModel()
{
    // Create and bind VAO, VBOs and EBO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &posVBO);
    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &norVBO);
    glBindBuffer(GL_ARRAY_BUFFER, norVBO);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &texVBO);
    glBindBuffer(GL_ARRAY_BUFFER, texVBO);
    glBufferData(GL_ARRAY_BUFFER, texcoords.size() * sizeof(float), texcoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    std::cout << "==INITIALIZING MODEL==" << '\n';
    std::cout << "vertices:  " << vertices.size() << '\n';
    std::cout << "normals:   " << normals.size() << '\n';
    std::cout << "texcoords: " << texcoords.size() << '\n';
    std::cout << "indices:   " << indices.size() << '\n';
    std::cout << "======================" << '\n';
}

void CheckOpenGLError(const char* location)
{
    GLenum error = glGetError();

    if (error != GL_NO_ERROR)
    {
        std::cout << "OpenGL error at " << location
                  << ": " << error << '\n';
    }
}

void Model::DrawModel()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}