#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "InputManager.h"
#include "PlayerController.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Shader.h"

void RenderScene(Renderer& renderer, Scene& scene);
void InitializeOpenGLParameters();
void InitializeScene(Scene& scene);

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

Camera* currCamera;

InputManager* globalInputManager;

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

    // Create input manager and player controller for player camera
    InputManager inputManager{window};
    globalInputManager = &inputManager;

    PlayerController playerController{inputManager};
    currCamera = &playerController.GetPlayerCamera();

    // Create resource manager and main scene
    ResourceManager resourceManager{};
    Scene mainScene{resourceManager};

    // Create main renderer
    Renderer renderer{shader, playerController.GetPlayerCamera()};
    // =========================================================

    InitializeOpenGLParameters();
    InitializeScene(mainScene);

    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // =============== MAIN RENDER LOOP ===============
        // Handle input
        playerController.Update(deltaTime);
        inputManager.EndFrame();

        // Render
        glClearColor(0.20f, 0.15f, 0.18f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        RenderScene(renderer, mainScene);
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
void InitializeScene(Scene& scene)
{
    // ==== OBJECT 0 - GROUND ====
    Object& ground = scene.AddObject(planeObjFilename, rockTextureFilename);
    ground.GetTransform().scaleVector = glm::vec3{2.0f};
    ground.GetTransform().positionVector = glm::vec3{0.0f, -5.0f, 0.0f};

    // ==== OBJECT 1 - WALLS =====

    /* Lambda expressions in C++: 
     * [capture_clause](parameter_list) -> return_type{body};
     * [&](int a) -> int{return a+1;};
     * return type does not always have to be specified explicitly: [&](int a) {return a+1;};
     * []:  cannot access variables from the enclosing scope, only global/static variables
     * [&]: capture all external variables by reference
     * [=]: capture all external variables by value
     * [a, &b]: capture 'a' by value and 'b' by reference
     */
    auto AddWall = [&](float rotationVectorY, glm::vec3 positionVector) {
        Object& wall = scene.AddObject(cubeObjFilename, wallTextureFilename);
        wall.GetTransform().scaleVector = glm::vec3{20.0f, 8.0f, 0.5f};
        wall.GetTransform().rotationVector.y = rotationVectorY;
        wall.GetTransform().positionVector = positionVector;
    };
    AddWall(0.0f, glm::vec3{0.0f, 0.0f, -20.0f});
    AddWall(90.0f, glm::vec3{-20.0f, 0.0f, 0.0f});
    AddWall(90.0f, glm::vec3{20.0f, 0.0f, 0.0f});
    AddWall(0.0f, glm::vec3{0.0f, 0.0f, 20.0f});

    // ==== OBJECT 2 - CAT ========
    Object& cat = scene.AddObject(catObjFilename, marbleTextureFilename);
    cat.GetTransform().scaleVector = glm::vec3{20.0f};
    cat.GetTransform().rotationVector.y = 30.0f;
    cat.GetTransform().positionVector = glm::vec3{7.0f, -3.0f, -8.f};

    // == CAMERA FIXED OBJECT 0 - SPHERE ==
    CameraFixedObject& sphere = scene.AddCameraFixedObject(sphereObjFilename, redTextureFilename);
    sphere.GetTransform().scaleVector = glm::vec3{0.5f};
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
void RenderScene(Renderer& renderer, Scene& scene)
{
    renderer.BeginFrame();

    for (Object& object : scene.GetObjects())
    {
        if (object.IsActive())
        {
            renderer.DrawObject(object);
        }
    }
    for (CameraFixedObject& cameraFixedObject : scene.GetCameraFixedObjects())
    {
        if (cameraFixedObject.IsActive())
        {
            cameraFixedObject.GetTransform().Translate(glm::vec3{0.0f, 0.0f, -0.1f});
            renderer.DrawCameraFixedObject(cameraFixedObject, renderer.GetCamera());  
        }  
    }
}

void CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    // Calculate current xpos and ypos difference from previous frame
    double deltaXpos = xpos - prevXpos;
    double deltaYpos = ypos - prevYpos;

    globalInputManager->SetCursorDeltaPos(deltaXpos, deltaYpos);

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