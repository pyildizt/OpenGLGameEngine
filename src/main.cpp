#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "Object.h"
#include "Shader.h"

void CreateMatrices(const Shader& shader);
void Display();
void InitializeObjects(const Shader& shader);
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

std::string wallTextureFilename = "assets/textures/wall.jpg";
std::string cubeObjFilename = "assets/models/cube.obj";
std::string vertexShaderFilepath = "shaders/vertex.glsl";
std::string fragmentShaderFilepath = "shaders/fragment.glsl";

std::vector<Model> models;
std::vector<Texture> textures;
std::vector<Object> objects;

int main()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS
#endif

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Intro Project", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Viewport
    glViewport(0, 0, 800, 600);

    // Handle window resizing
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    // Initialize objects and shaders
    Shader shader{vertexShaderFilepath, fragmentShaderFilepath};
    shader.ActivateShaderProgram();
    InitializeObjects(shader);

    // Main render loop
    while (!glfwWindowShouldClose(window))
    {
        // Handle input
        ProcessInput(window);

        // Render
        glClearColor(0.20f, 0.15f, 0.18f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        CreateMatrices(shader);
        Display();

        // Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

/// <summary>
/// Create models and objects
/// </summary>
void InitializeObjects(const Shader& shader)
{
    models.reserve(100);
    textures.reserve(100);
    objects.reserve(100);

    models.emplace_back(cubeObjFilename);
    std::cout << "after model\n";

    textures.emplace_back(wallTextureFilename);
    std::cout << "after texture\n";

    models[0].SetTexture(textures[0]);
    shader.SetInt(shader.GetUniformLocation("myTexture"), 0);
    std::cout << "after SetTexture\n";
   
    objects.emplace_back(models[0]);
    std::cout << "after object\n";

    glEnable(GL_DEPTH_TEST);
}

/// <summary>
/// Create transformation, model, view, projection matrices and send them to the vertex shader
/// </summary>
void CreateMatrices(const Shader& shader)
{
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5));  
    shader.SetMat4(shader.GetUniformLocation("transform"), transform);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    shader.SetMat4(shader.GetUniformLocation("model"), model);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
    shader.SetMat4(shader.GetUniformLocation("view"), view);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    shader.SetMat4(shader.GetUniformLocation("projection"), projection);
}

/// <summary>
/// Continuously draw elements on screen 
/// </summary>
void Display()
{
    objects[0].DrawObject();
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}