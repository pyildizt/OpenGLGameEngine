#ifndef MODEL_H
#define MODEL_H

#include "Texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

class Model
{
private:
    GLuint VAO, posVBO, norVBO, texVBO, EBO;

    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texcoords;
    std::vector<unsigned int> indices;

    Texture* texture;

public:
    Model(const std::string& modelFilename);

    void SetTexture(Texture& newTexture);
    Texture* GetTexture();

    bool LoadModelFromObj(const std::string& modelFilename);
    void InitializeModel();
    void DrawModel();
};

#endif