#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <ostream>
#include <string>
#include <glm/glm.hpp>

#include "Camera/Camera.h"
#include "Camera/CameraController.h"
#include "Core/CollisionSystem.h"
#include "Core/Game.h"
#include "Core/InputManager.h"
#include "Core/PlayerController.h"
#include "Core/Scene.h"
#include "Rendering/Renderer.h"
#include "Scene/RenderObject.h"
#include "Utilities/Utils.h"

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
    GLFWwindow* window = glfwCreateWindow(960, 640, "OpenGL Intro Project", nullptr, nullptr);
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

    // =============== INITIALIZE MAIN GAME ===============
    Game game{window};
    globalGame = &game;

    InitializeOpenGLParameters();
    InitializeScene(game.GetCurrScene());
    game.GetCameraController().SetCamera(*game.GetCurrScene().GetCameras().back());

    game.GetRenderer().GetColliderRenderer().SetShowColliders(true);
    game.GetRenderer().GetGridRenderer().SetShowGrid(true);
    // ====================================================

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
        renderer.RenderScene(currScene);

        // Render player collider
        renderer.GetColliderRenderer().DrawCollider(game.GetPlayerController(), renderer.GetShader());
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
    RenderObject& cat = scene.AddRenderObject(catObjFilename);
    cat.GetLocalTransform().scaleVector = glm::vec3{10.0f};
    cat.GetLocalTransform().SetRotationEuler(glm::vec3{0.0f, 30.f, 0.0f});
    cat.GetLocalTransform().positionVector = glm::vec3{7.0f, 0.5f, -8.f};
    cat.SetColor(RGBAtoVec4(188, 143, 196, 200));

    // === RENDER OBJECT 0 - SPHERES ===
    RenderObject& sphere1 = scene.AddRenderObject(sphereObjFilename);
    sphere1.GetLocalTransform().scaleVector = glm::vec3{0.5f};
    sphere1.SetColor(RGBAtoVec4(180, 0, 0, 255));
    sphere1.GetLocalTransform().positionVector = glm::vec3{0.0f, 1.0f, 0.0f};

    RenderObject& sphere2 = scene.AddRenderObject(sphereObjFilename);
    sphere2.GetLocalTransform().scaleVector = glm::vec3{0.5f};
    sphere2.SetColor(RGBAtoVec4(0, 180, 0, 255));
    sphere2.GetLocalTransform().positionVector = glm::vec3{3.0f, 1.0f, 0.0f};

    RenderObject& sphere3 = scene.AddRenderObject(sphereObjFilename);
    sphere3.GetLocalTransform().scaleVector = glm::vec3{1.0f};
    sphere3.SetColor(RGBAtoVec4(0, 0, 180, 255));
    sphere3.GetLocalTransform().positionVector = glm::vec3{3.0f, 1.0f, 0.0f};
    sphere3.SetParent(&sphere1);

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
    if (action != GLFW_PRESS)
        return;

    switch(key) 
    {
    case GLFW_KEY_ESCAPE: 
        if (mods == GLFW_MOD_ALT) // quit
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
    case GLFW_KEY_H: // help - print help
        std::cout << "=======================\nAlt+Esc: Quit\nEsc: Change cursor mode\nJ: Player camera\nK: Scene camera\nC: Show colliders\n=======================" << std::endl;
        break;
    case GLFW_KEY_K: // change camera to scene camera
        globalGame->GetPlayerController().SetActive(false);
        globalGame->GetCameraController().SetActive(true);
        globalGame->GetRenderer().SetCamera(*globalGame->GetCurrScene().GetCameras().back());
        break;
    case GLFW_KEY_J: // change camera to player camera
        globalGame->GetPlayerController().SetActive(true);
        globalGame->GetCameraController().SetActive(false);
        globalGame->GetRenderer().SetCamera(globalGame->GetPlayerController().GetPlayerCamera());
        break;
    case GLFW_KEY_C: // toggle show colliders
        globalGame->GetRenderer().GetColliderRenderer().SetShowColliders(
            !globalGame->GetRenderer().GetColliderRenderer().ShowColliders()
        );
        break;
    case GLFW_KEY_G: // toggle show grid
        globalGame->GetRenderer().GetGridRenderer().SetShowGrid(
            !globalGame->GetRenderer().GetGridRenderer().ShowGrid()
        );
        break;
    }
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}