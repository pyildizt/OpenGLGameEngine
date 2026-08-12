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

    for (const auto& index : shapes[0].mesh.indices)
    {
        Vertex vertex;
        vertex.position = glm::vec3(attrib.vertices[index.vertex_index * 3],
                                    attrib.vertices[index.vertex_index * 3 + 1],
                                    attrib.vertices[index.vertex_index * 3 + 2]);
        vertex.normal =   glm::vec3(attrib.normals[index.normal_index * 3],
                                    attrib.normals[index.normal_index * 3 + 1],
                                    attrib.normals[index.normal_index * 3 + 2]);
        vertex.texcoord = glm::vec2(attrib.texcoords[index.texcoord_index * 2],
                                    attrib.texcoords[index.texcoord_index * 2 + 1]);

        vertices.push_back(vertex);
    }
    return true;
}

void Model::InitializeModel()
{
    // Create and bind VAO, VBOs and EBO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
    glEnableVertexAttribArray(2);

    // glGenBuffers(1, &EBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    std::cout << "==INITIALIZING MODEL==" << '\n';
    std::cout << "indices:  " << vertices.size() << '\n';
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

    glActiveTexture(GL_TEXTURE0);
    texture->BindTexture();
    
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    // glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}