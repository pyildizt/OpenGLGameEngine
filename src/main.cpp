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
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window, float deltaTime);

std::string vertexShaderFilepath = "shaders/vertex.glsl";
std::string fragmentShaderFilepath = "shaders/fragment.glsl";

std::string rockTextureFilename = "assets/textures/rock.jpg";
std::string wallTextureFilename = "assets/textures/wall.jpg";
std::string marbleTextureFilename = "assets/textures/marble.jpg";
std::string redTextureFilename = "assets/textures/red.jpg";
std::string catTextureFilename = "assets/textures/concrete_cat_statue_diff_1k.jpg";

std::string planeObjFilename = "assets/models/plane.obj";
std::string cubeObjFilename = "assets/models/cube.obj";
std::string sphereObjFilename = "assets/models/sphere.obj";
std::string catObjFilename = "assets/models/cat/concrete_cat_statue_1k.obj";

std::vector<Model> models;
std::vector<Texture> textures;
std::vector<Object> objects;
std::vector<Camera> cameras;
Camera* currCamera;
Projection projection;

float deltaTime{0.0f}, lastFrame{0.0f};
double prevXpos{1080.0f/2}, prevYpos{720.0f/2};

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
    int frameWidth, frameHeight;
    glfwGetFramebufferSize(window, &frameWidth, &frameHeight);
    glViewport(0, 0, frameWidth, frameHeight);

    // Lock cursor for FPS type camera
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set callbacks
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, CursorPosCallback);
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
    int currObjectIndex = -1;
    models.reserve(10);
    textures.reserve(10);
    objects.reserve(10);

    // ==== OBJECT 0 - GROUND ====
    models.emplace_back(planeObjFilename);
    textures.emplace_back(rockTextureFilename);
    models[0].SetTexture(textures[0]);
    objects.emplace_back(models[0]);
    currObjectIndex++;
    
    objects[currObjectIndex].GetTransform().SetScale(glm::vec3{2.0f});
    objects[currObjectIndex].GetTransform().SetPosition(glm::vec3{0.0f, -5.0f, 0.0f});
    // ===========================

    // ==== OBJECT 1 - WALLS =====
    models.emplace_back(cubeObjFilename);
    textures.emplace_back(wallTextureFilename);
    models[1].SetTexture(textures[1]);

    for (int i=1; i<5; i++)
    {
        objects.emplace_back(models[1]);
        objects[currObjectIndex + i].GetTransform().SetScale(glm::vec3{20.0f, 8.0f, 0.5f});   
    }
    objects[currObjectIndex + 1].GetTransform().SetPosition(glm::vec3{0.0f, 0.0f, -20.0f});    

    objects[currObjectIndex + 2].GetTransform().SetRotationY(90.f);
    objects[currObjectIndex + 2].GetTransform().SetPosition(glm::vec3{-20.0f, 0.0f, 0.0f});    

    objects[currObjectIndex + 3].GetTransform().SetRotationY(90.f);
    objects[currObjectIndex + 3].GetTransform().SetPosition(glm::vec3{20.0f, 0.0f, 0.0f});  

    objects[currObjectIndex + 4].GetTransform().SetPosition(glm::vec3{0.0f, 0.0f, 20.0f}); 

    currObjectIndex += 4;
    //objects[1].GetTransform().SetPosition(glm::vec3{6.0f, -4.5f, -20.0f});
    // ============================

    // ==== OBJECT 2 - CAT ========
    models.emplace_back(catObjFilename);
    textures.emplace_back(marbleTextureFilename);
    models[2].SetTexture(textures[2]);
    objects.emplace_back(models[2]);
    currObjectIndex++;

    objects[currObjectIndex].GetTransform().SetTransformValues(
        glm::vec3{20.0f}, 
        glm::vec3{0.0f, 30.f, 0.0f}, 
        glm::vec3{7.0f, -3.0f, -8.f});
    // ============================

    // ==== OBJECT 3 - SPHERE =====
    models.emplace_back(cubeObjFilename);
    textures.emplace_back(redTextureFilename);
    models[3].SetTexture(textures[3]);
    objects.emplace_back(models[3]);
    currObjectIndex++;

    objects[currObjectIndex].GetTransform().SetTransformValues(
        glm::vec3{0.0001f}, 
        glm::vec3{0.0f, 30.f, 0.0f}, 
        glm::vec3{-4.0f, 0.5f, 9.f});

    objects[currObjectIndex].SetActive(false);
    // ============================
}

/// <summary>
/// Modify builtin OpenGL parameters before render loop
/// </summary>
void InitializeOpenGLParameters()
{
    glEnable(GL_DEPTH_TEST);
}

glm::vec3 tempGlobalPositionVector{0.0f, 0.0f, 0.0f};
float tempGlobalRotationYAmount{0.0f};

/// <summary>
/// Continuously draw elements on screen 
/// </summary>
void Render(Renderer& renderer)
{
    renderer.BeginFrame();

    //objects[1].GetTransform().RotateRelativeY(100.0f * deltaTime);

    for (Object& object : objects)
    {
        if (object.IsActive())
        {
            renderer.DrawObject(object);
        }
        else
        {
            Camera& camera = renderer.GetCamera();
            camera.CalculateCameraVectors();

            glm::vec3 positionVector = renderer.GetCamera().GetPositionVector() + renderer.GetCamera().GetForwardVector() * 4.5f;

            // Camera basis to object's basis
            glm::mat4 model{1.0f};
            model[0] = glm::vec4(camera.GetRightVector(),    0.0f);
            model[1] = glm::vec4(camera.GetUpVector(),       0.0f);
            model[2] = glm::vec4(-camera.GetForwardVector(), 0.0f);
            model[3] = glm::vec4(positionVector, 1.0f);

            tempGlobalPositionVector.x += 0.01f;
            model = glm::translate(model, tempGlobalPositionVector);
            //model = glm::translate(model, glm::vec3{2.0f, 1.0f, 0.0f});
            
            tempGlobalRotationYAmount += 1.0f;
            model = glm::rotate(model, glm::radians(tempGlobalRotationYAmount), glm::vec3{1.0f, 1.0f, 0.0f});
            //model = glm::rotate(model, glm::radians(45.f), glm::vec3{1.0f, 1.0f, 0.0f});
            
            model = glm::scale(model, glm::vec3{0.2f});

            renderer.GetShader().SetMat4(renderer.GetShader().GetUniformLocation("model"), model);
            object.DrawObject();
        }
    }
}

/// <summary>
/// Process user input relative to delta time
/// </summary>
void ProcessInput(GLFWwindow* window, float deltaTime)
{
    // Handle camera movement with WASD for FPS style camera
    float distanceAmount = 10.0f;
    float x, y, z;

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

void CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    // Handle camera rotation for FPS type camera 
    double mouseSensitivity = 0.5;

    double deltaXpos = xpos - prevXpos; // if result is positive then the mouse moved to the right
    double deltaYpos = ypos - prevYpos; // if result is positive then the mouse moved up

    // Handle horizontal rotation
    double rotationAmount = deltaXpos * mouseSensitivity;
    currCamera->RotateRelative(glm::vec3{0.0f, -rotationAmount, 0.0f});

    // Handle vertical rotation
    rotationAmount = deltaYpos * mouseSensitivity;
    currCamera->RotateRelative(glm::vec3{-rotationAmount, 0.0f, 0.0f});

    // Update prev xpos and ypos
    prevXpos = xpos;
    prevYpos = ypos;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch(key) 
    {
    case GLFW_KEY_ESCAPE: // quit
        glfwSetWindowShouldClose(window, true);
        exit(EXIT_SUCCESS);
        break;
    case GLFW_KEY_R: // reset camera rotation
        currCamera->SetRotation(glm::vec3{0.0f});
        break;
    case GLFW_KEY_T: // reset camera rotation
        currCamera->SetRotation(glm::vec3{0.0f, 90.0f, 0.0f});
        break;
    case GLFW_KEY_Y: // reset camera rotation
        currCamera->SetRotation(glm::vec3{0.0f, 180.0f, 0.0f});
        break;
    case GLFW_KEY_U: // reset camera rotation
        currCamera->SetRotation(glm::vec3{-90.0f, 00.0f, 0.0f});
        break;
    }
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}