#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "Camera.h"
#include "Object.h"
#include "Projection.h"
#include "Renderer.h"
#include "Shader.h"

void Render(const Renderer& renderer);
void InitializeOpenGLParameters();
void InitializeObjects();
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

std::string vertexShaderFilepath = "shaders/vertex.glsl";
std::string fragmentShaderFilepath = "shaders/fragment.glsl";

std::string wallTextureFilename = "assets/textures/wall.jpg";
std::string catTextureFilename = "assets/textures/concrete_cat_statue_diff_1k.jpg";

std::string cubeObjFilename = "assets/models/cube.obj";
std::string catObjFilename = "assets/models/cat/concrete_cat_statue_1k.obj";

std::vector<Model> models;
std::vector<Texture> textures;
std::vector<Object> objects;
std::vector<Camera> cameras;
Projection projection;

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

    // =============== INITIALIZE MAIN RENDERER ===============
    // Create and activate shader
    Shader shader{vertexShaderFilepath, fragmentShaderFilepath};
    shader.ActivateShaderProgram();

    // Create perspective projection
    Projection projection{};

    // Create main camera
    cameras.reserve(10);
    cameras.emplace_back();

    // Create main renderer
    Renderer renderer{shader, projection, cameras[0]};
    // =========================================================

    InitializeOpenGLParameters();
    InitializeObjects();

    while (!glfwWindowShouldClose(window))
    {
        // =============== MAIN RENDER LOOP ===============
        // Handle input
        ProcessInput(window);

        // Render
        glClearColor(0.20f, 0.15f, 0.18f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Render(renderer);
        // ================================================

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
void InitializeObjects()
{
    models.reserve(10);
    textures.reserve(10);
    objects.reserve(10);

    // ==== OBJECT 0 ====
    models.emplace_back(cubeObjFilename);
    textures.emplace_back(wallTextureFilename);
    models[0].SetTexture(textures[0]);
    objects.emplace_back(models[0]);

    objects[0].GetTransform().SetTransformValues(glm::vec3{0.5f}, glm::vec3{-55.0f, 0.0f, 0.0f}, glm::vec3{0.0f});
    // ==================

    // ==== OBJECT 1 ====
    // models.emplace_back(catObjFilename);
    // textures.emplace_back(catTextureFilename);
    // models[1].SetTexture(textures[1]);
    // objects.emplace_back(models[1]);
    // ==================
}

/// <summary>
/// Modify builtin OpenGL parameters before render loop
/// </summary>
void InitializeOpenGLParameters()
{
    glEnable(GL_DEPTH_TEST);
}

/// <summary>
/// Continuously draw elements on screen 
/// </summary>
void Render(const Renderer& renderer)
{
    objects[0].GetTransform().SetRotationZ((float)glfwGetTime());
    renderer.DrawObject(objects[0]);
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