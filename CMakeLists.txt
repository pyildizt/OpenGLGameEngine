cmake_minimum_required(VERSION 3.20)

project(OpenGLGameEngine VERSION 0.1.0 LANGUAGES C CXX)

# ============================================
# C++ Standard
# ============================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ============================================
# Locate GLAD
# ============================================

set(GLAD_ROOT "${CMAKE_SOURCE_DIR}/external/glad")

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

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(${PROJECT_NAME}
    ${SRC_FILES}
    ${GLAD_ROOT}/src/glad.c
)

# ============================================
# Include directories
# ============================================

target_include_directories(${PROJECT_NAME} PRIVATE
    include
    external/stb
    external/tinyobjloader
    ${GLAD_ROOT}/include
)

# ============================================
# Link libraries
# ============================================

target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    glfw
    glm::glm
)

# ============================================
# Copy shaders folder into the build directory
# ============================================

add_custom_target(CopyShaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
)
add_dependencies(${PROJECT_NAME} CopyShaders)

# ============================================
# Compiler warnings
# ============================================

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
    )
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -pedantic
    )
endif()

# ============================================
# Copy assets folder into the build directory
# ============================================

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)