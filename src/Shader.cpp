#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader()
{
    // Initialize vertex shader
    std::string vertexCode = readShaderFile("shaders/vertex.glsl");
    const char* vertexShaderSource = vertexCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check vertex shader
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Initialize fragment shader
    std::string fragmentCode = readShaderFile("shaders/fragment.glsl");
    const char* fragmentShaderSource = fragmentCode.c_str();

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check fragment shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Create shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check shader program
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Delete shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint Shader::ShaderProgram() const
{
    return shaderProgram;
}

void Shader::ActivateShaderProgram() const
{
    glUseProgram(shaderProgram);
}

void Shader::DeleteShaderProgram() const
{
    glDeleteProgram(shaderProgram);
}

std::string Shader::readShaderFile(const std::string& filepath)
{
    std::ifstream file(filepath);
    if (!file)
    {
        throw std::runtime_error("Failed to open shader: " + filepath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint Shader::GetUniformLocation(const std::string& name) const
{
    return glGetUniformLocation(shaderProgram, name.c_str());
}

void Shader::SetVec3(const GLuint location, const glm::vec3 val) const
{
    glUniform3f(location, val.x, val.y, val.z);
}

void Shader::SetVec4(const GLuint location, const glm::vec4 val) const
{
    glUniform4f(location, val.x, val.y, val.z, val.w);
}

void Shader::SetMat4(const GLuint location, const glm::mat4& val) const
{
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(val));
}