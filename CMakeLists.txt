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
find_package(glm REQUIRED)

# ============================================
# Executable
# ============================================

file(GLOB SRC_FILES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(OpenGLIntroProject
    ${SRC_FILES}
    ${GLAD_ROOT}/src/glad.c
)

# ============================================
# Include directories
# ============================================

target_include_directories(OpenGLIntroProject PRIVATE
    include
    external/stb
    external/tinyobjloader
    ${GLAD_ROOT}/include
)

# ============================================
# Link libraries
# ============================================

target_link_libraries(OpenGLIntroProject PRIVATE
    OpenGL::GL
    glfw
    glm::glm
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

# ============================================
# Copy shaders folder into the build directory
# ============================================

add_custom_command(TARGET OpenGLIntroProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:OpenGLIntroProject>/shaders
)

add_custom_command(TARGET OpenGLIntroProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:OpenGLIntroProject>/assets
)