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

void Render(Renderer& renderer);
void InitializeOpenGLParameters();
void InitializeObjects();

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window, float deltaTime);

std::string vertexShaderFilepath = "shaders/vertex.glsl";
std::string fragmentShaderFilepath = "shaders/fragment.glsl";

std::string rockTextureFilename = "assets/textures/rock.jpg";
std::string wallTextureFilename = "assets/textures/wall.jpg";
std::string catTextureFilename = "assets/textures/concrete_cat_statue_diff_1k.jpg";

std::string planeObjFilename = "assets/models/plane.obj";
std::string cubeObjFilename = "assets/models/cube.obj";
std::string catObjFilename = "assets/models/cat/concrete_cat_statue_1k.obj";

std::vector<Model> models;
std::vector<Texture> textures;
std::vector<Object> objects;
std::vector<Camera> cameras;
Camera* currCamera;
Projection projection;

float deltaTime{0.0f};
float lastFrame{0.0f};

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

    // Set callbacks
    glfwSetKeyCallback(window, KeyCallback);
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
    currCamera = &cameras[0];

    // Create main renderer
    Renderer renderer{shader, projection, cameras[0]};
    // =========================================================

    InitializeOpenGLParameters();
    InitializeObjects();

    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // =============== MAIN RENDER LOOP ===============
        // Handle input
        ProcessInput(window, deltaTime);

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
    models.emplace_back(planeObjFilename);
    textures.emplace_back(rockTextureFilename);
    models[0].SetTexture(textures[0]);
    objects.emplace_back(models[0]);

    objects[0].GetTransform().SetScale(glm::vec3{2.0f});
    objects[0].GetTransform().SetPosition(glm::vec3{0.0f, -5.0f, -30.0f});
    // ==================

    // ==== OBJECT 1 ====
    models.emplace_back(cubeObjFilename);
    textures.emplace_back(wallTextureFilename);
    models[1].SetTexture(textures[1]);
    objects.emplace_back(models[1]);

    objects[1].GetTransform().SetPosition(glm::vec3{6.0f, -4.5f, -20.0f});
    // ==================

    // ==== OBJECT 2 ====
    models.emplace_back(catObjFilename);
    textures.emplace_back(catTextureFilename);
    models[2].SetTexture(textures[2]);
    objects.emplace_back(models[2]);

    objects[2].SetActive(false);
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
void Render(Renderer& renderer)
{
    renderer.BeginFrame();

    objects[1].GetTransform().RotateRelativeY(100.0f * deltaTime);

    for (Object& object : objects)
    {
        if (object.IsActive()) {
            renderer.DrawObject(object);
        }
    }
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/// <summary>
/// Process user input relative to delta time
/// </summary>
void ProcessInput(GLFWwindow* window, float deltaTime)
{
    // Camera movement with WASD + QE for rotation -> upgrade to mouse movement
    float distanceAmount = 10.0f;
    float rotationAmount = 15.0f;
    float x, y, z;

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        currCamera->RotateRelative(glm::vec3{0.0f, rotationAmount, 0.0f} * deltaTime);
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        currCamera->RotateRelative(glm::vec3{0.0f, -rotationAmount, 0.0f} * deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        y = currCamera->GetRotationVector().y;
        x = -sin(glm::radians(y));
        z = -cos(glm::radians(y));
        currCamera->Translate(glm::vec3{x, 0.0f, z} * distanceAmount * deltaTime);
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        y = currCamera->GetRotationVector().y;
        x = sin(glm::radians(y));
        z = cos(glm::radians(y));
        currCamera->Translate(glm::vec3{x, 0.0f, z} * distanceAmount * deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        y = currCamera->GetRotationVector().y;
        x = -cos(glm::radians(y));
        z = sin(glm::radians(y));
        currCamera->Translate(glm::vec3{x, 0.0f, z} * distanceAmount * deltaTime);
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        y = currCamera->GetRotationVector().y;
        x = cos(glm::radians(y));
        z = -sin(glm::radians(y));
        currCamera->Translate(glm::vec3{x, 0.0f, z} * distanceAmount * deltaTime);
    }
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch(key) 
    {
    case GLFW_KEY_ESCAPE: // quit
        glfwSetWindowShouldClose(window, true);
        exit(EXIT_SUCCESS);
        break;
    }
}