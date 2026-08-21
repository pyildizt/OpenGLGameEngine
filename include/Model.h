#ifndef MODEL_H
#define MODEL_H

#include "Texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;
};

class Model
{
private:
    GLuint VAO, VBO, EBO;

    std::vector<Vertex> vertices;

    Texture* texture;

public:
    Model(const std::string& modelFilename);

    void SetTexture(Texture& newTexture);
    const Texture* GetTexture() const;

    bool LoadModelFromObj(const std::string& modelFilename);
    void InitializeModel();

    void DrawModel() const;
};

#endif