#ifndef MODEL_H
#define MODEL_H

#include "Rendering/Texture.h"

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
    const std::string& filename;

    GLuint VAO, VBO, EBO;

    std::vector<Vertex> vertices;

    Texture* texture{nullptr};

    bool LoadModelFromObj(const std::string& modelFilename);
    void InitializeModel();

public:
    Model(const std::string& modelFilename);

    const std::string& GetModelFilename() const;

    void SetTexture(Texture& newTexture);
    const Texture& GetTexture() const;
    bool HasTexture() const;

    void DrawModel() const;
};

#endif