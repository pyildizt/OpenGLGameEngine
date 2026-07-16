cmake_minimum_required(VERSION 3.20)

project(OpenGLIntroProject VERSION 0.1.0 LANGUAGES C CXX)

# ============================================
# C++ Standard
# ============================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ============================================
# Locate GLAD
# ============================================

if(WIN32)
    set(GLAD_ROOT "$ENV{USERPROFILE}/OpenGL")
elseif(APPLE)
    set(GLAD_ROOT "$ENV{HOME}/OpenGL")
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

if(NOT EXISTS "${GLAD_ROOT}/include/glad/glad.h")
    message(FATAL_ERROR "GLAD not found! Expected it at: ${GLAD_ROOT}")
endif()

# ============================================
# Find packages
# ============================================

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# ============================================
# Executable
# ============================================

add_executable(OpenGLIntroProject
    src/main.cpp
    ${GLAD_ROOT}/src/glad.c
)

# ============================================
# Include directories
# ============================================

target_include_directories(OpenGLIntroProject PRIVATE
    include
    ${GLAD_ROOT}/include
)

# ============================================
# Link libraries
# ============================================

target_link_libraries(OpenGLIntroProject PRIVATE
    OpenGL::GL
    glfw
)

# ============================================
# Compiler warnings
# ============================================

if(MSVC)
    target_compile_options(OpenGLIntroProject PRIVATE
        /W4
    )
else()
    target_compile_options(OpenGLIntroProject PRIVATE
        -Wall
        -Wextra
        -pedantic
    )
endif()

