# C++ OpenGL Game Engine & FPS

A personal C++/OpenGL project focused on building a small game engine and FPS game from scratch.

## About

This is an ongoing personal project written in C++ and OpenGL.

The goal is to learn about game-engine architecture, gameplay systems, rendering, and C++ project organization by implementing the systems myself and only using external libraries if necessary.

The engine currently includes a hierarchical scene system, resource management, rendering, collision detection, player and camera control systems, and early editor functionality.

## Features

#### Rendering
- OpenGL rendering pipeline
- GLSL shaders
- OBJ model loading
- Texture loading
- Perspective projection
- External scene cameras

#### Scene System
- Hierarchical scene nodes
- Parent-child transforms
- Quaternion-based rotations
- Render objects and game objects
- Resource management

#### Gameplay
- Player controller
- AABB collision detection
- Camera-based movement

#### Editor
- Mouse-based object selection using color-based picking
- Runtime object manipulation
- Grid and collider visualization
- Editor camera controller

## Building

### macOS
#### Requirements
- CMake 3.20 or newer
- C++17-compatible compiler
- Homebrew
- GLFW and GLM (install with `brew install cmake glfw glm`)

GLAD is included in the repository under external/glad

#### Build
- Configure project: `cmake -S . -B build`
- Build the project: `cmake --build build --config Release`
- Run the executable: `./build/OpenGLGameEngine`

### Windows
#### Requirements
- Visual Studio with the C++ development tools
- CMake 3.20 or newer
- vcpkg
- GLFW and GLM (install with `vcpkg install glfw3 glm`)

GLAD is included in the repository under external/glad

#### Build
- Configure project: `cmake --preset windows`
- Build the project: `cmake --build build/windows --config Release`
- Run the executable: `.\build\windows\Release\OpenGLGameEngine.exe`

## Credits
### Libraries
- [GLFW](https://github.com/glfw/glfw) - Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan application development
- [GLAD](https://github.com/Dav1dde/glad) - Vulkan/GL/GLES/EGL/GLX/WGL Loader-Generator 
- [GLM](https://github.com/g-truc/glm) - A header only C++ mathematics library for graphics software
- [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader) v2.0.0 - Tiny but powerful Wavefront .obj/.mtl loader
- [stb_image](https://github.com/nothings/stb) v2.30 - Public domain image loader

### Assets
Models and textures used in the project are stored in the assets/ directory. 
Asset sources and licenses can be found in the [Assets.md](Assets.md) file. 

