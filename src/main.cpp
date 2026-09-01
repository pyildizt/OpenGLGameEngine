#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <glm/glm.hpp>

#include "Camera.h"
#include "CameraController.h"
#include "CollisionSystem.h"
#include "Game.h"
#include "ICollidable.h"
#include "InputManager.h"
#include "PlayerController.h"
#include "Renderer.h"
#include "Scene.h"
#include "Utils.h"

void InitializeOpenGLParameters();
void InitializeScene(Scene& scene);

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window, float deltaTime);

std::string rockTextureFilename = "assets/textures/rock.jpg";
std::string wallTextureFilename = "assets/textures/wall.jpg";
std::string marbleTextureFilename = "assets/textures/marble.jpg";
std::string redTextureFilename = "assets/textures/red.jpg";
std::string catTextureFilename = "assets/textures/concrete_cat_statue_diff_1k.jpg";

std::string planeObjFilename = "assets/models/plane.obj";
std::string cubeObjFilename = "assets/models/cube.obj";
std::string sphereObjFilename = "assets/models/sphere.obj";
std::string catObjFilename = "assets/models/cat/concrete_cat_statue_1k.obj";

Game* globalGame;
float deltaTime{0.0f}, lastFrame{0.0f};

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
#ifdef __APPLE__
    GLFWwindow* window = glfwCreateWindow(1080, 720, "OpenGL Intro Project", nullptr, nullptr);
#else
    GLFWwindow* window = glfwCreateWindow(3200, 1800, "OpenGL Intro Project", nullptr, nullptr);
#endif
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
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    // =============== INITIALIZE MAIN RENDERER ===============
    /*
    // Create and activate shader
    Shader shader{vertexShaderFilepath, fragmentShaderFilepath};
    shader.ActivateShaderProgram();

    // Create input manager and player controller for player camera
    InputManager inputManager{window};
    globalInputManager = &inputManager;

    PlayerController playerController{inputManager};
    globalPlayerController = &playerController;
    currCamera = &playerController.GetPlayerCamera();

    CameraController cameraController{inputManager};
    globalCameraController = &cameraController;
    cameraController.SetCamera(*currCamera);

    // Create collision system
    CollisionSystem collisionSystem{};

    // Create resource manager and main scene
    ResourceManager resourceManager{};
    Scene mainScene{resourceManager};
    globalScene = &mainScene;

    // Create main renderer
    Renderer renderer{shader, playerController.GetPlayerCamera()};
    globalRenderer = &renderer;
    */

    Game game{window};
    globalGame = &game;
    // =========================================================

    InitializeOpenGLParameters();
    InitializeScene(game.GetCurrScene());
    game.GetCameraController().SetCamera(*game.GetCurrScene().GetCameras().back());

    game.GetRenderer().SetShowColliders(true);

    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // =============== MAIN RENDER LOOP ===============
        Renderer& renderer = game.GetRenderer();
        Scene& currScene = game.GetCurrScene();
        // Handle input
        game.GetPlayerController().Update(deltaTime);
        game.GetCameraController().Update(deltaTime);
        game.GetInputManager().EndFrame();

        // Check object collisions with player
        game.GetCollisionSystem().Update(game.GetPlayerController(), currScene);

        // Render scene
        game.GetRenderer().RenderScene(currScene);

        // Render colliders
        renderer.DrawColliders(currScene);
        renderer.DrawCollider(game.GetPlayerController());
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
    GameObject& ground = scene.AddGameObject(planeObjFilename, rockTextureFilename);
    ground.SetObjectName("ground");
    ground.GetLocalTransform().scaleVector = glm::vec3{2.0f};
    ground.GetLocalTransform().positionVector = glm::vec3{0.0f, 0.0f, 0.0f};
    // ground.UseTexture(false);
    ground.SetColor(RGBAtoVec4(29, 43, 35, 255));
    ground.SetCollider(Collider{ColliderShape::Box, 0.0f, {10.0f, 0.0f, 10.0f}});

    GameObject& o = scene.AddGameObject(planeObjFilename, rockTextureFilename);
    o.GetLocalTransform().positionVector = glm::vec3{30.0f, 0.0f, 0.0f};

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
    auto AddWall = [&](glm::vec3 scaleVector, glm::vec3 positionVector) {
        GameObject& wall = scene.AddGameObject(cubeObjFilename, wallTextureFilename);
        wall.SetObjectName("wall");
        wall.GetLocalTransform().scaleVector = scaleVector;
        wall.GetLocalTransform().positionVector = positionVector;
        wall.SetCollider(Collider{ColliderShape::Box, 0.0f, glm::vec3{1.0f}, glm::vec3{0.0f}});
    };
    AddWall(glm::vec3{20.0f, 3.0f, 0.5f}, glm::vec3{0.0f, 1.5f, 20.0f});
    AddWall(glm::vec3{20.0f, 3.0f, 0.5f}, glm::vec3{0.0f, 1.5f, -20.0f});
    AddWall(glm::vec3{0.5f, 3.0f, 20.0f}, glm::vec3{-20.0f, 1.5f, 0.0f});
    //AddWall(glm::vec3{0.5f, 3.0f, 20.0f}, glm::vec3{20.0f, 1.5f, 0.0f});
    
    // ==== OBJECT 2 - CAT ========
    GameObject& cat = scene.AddGameObject(catObjFilename);
    cat.SetObjectName("cat");
    cat.GetLocalTransform().scaleVector = glm::vec3{10.0f};
    cat.GetLocalTransform().SetRotationEuler(glm::vec3{0.0f, 30.f, 0.0f});
    cat.GetLocalTransform().positionVector = glm::vec3{7.0f, 0.5f, -8.f};
    cat.SetCollider(Collider{ColliderShape::Box, 0.0f, glm::vec3{0.05f, 0.1f, 0.05f}, glm::vec3{0.0f, 0.05f, 0.0f}});
    cat.SetColor(RGBAtoVec4(188, 143, 196, 200));

    // == CAMERA FIXED OBJECT 0 - SPHERE ==
    //CameraFixedObject& sphere = scene.AddCameraFixedObject(sphereObjFilename, redTextureFilename);
    //sphere.GetTransform().scaleVector = glm::vec3{0.5f};

    // ===== CAMERA 0 =============
    Camera& camera = scene.AddCamera();
    camera.GetLocalTransform().positionVector = glm::vec3{2.0f, 2.0f, 1.0f};
    camera.GetLocalTransform().SetRotationEuler(glm::vec3{0.0f, 0.0f, 0.0f});
}

/// <summary>
/// Modify builtin OpenGL parameters before render loop
/// </summary>
void InitializeOpenGLParameters()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch(key) 
    {
    case GLFW_KEY_ESCAPE: 
        if (mods == GLFW_MOD_ALT && action == GLFW_PRESS) // quit
        {
            glfwSetWindowShouldClose(window, true);
            exit(EXIT_SUCCESS);
        }
        else
        {
            if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            else
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        break;
    case GLFW_KEY_H: // change camera to scene camera
        globalGame->GetPlayerController().SetActive(false);
        globalGame->GetCameraController().SetActive(true);
        globalGame->GetRenderer().SetCamera(*globalGame->GetCurrScene().GetCameras().back());
        break;
    case GLFW_KEY_J: // change camera to player camera
        globalGame->GetPlayerController().SetActive(true);
        globalGame->GetCameraController().SetActive(false);
        globalGame->GetRenderer().SetCamera(globalGame->GetPlayerController().GetPlayerCamera());
        break;
    }
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}