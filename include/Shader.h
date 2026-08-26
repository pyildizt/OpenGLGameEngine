#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader
{
private:
	GLuint shaderProgram{};

	std::string ReadShaderFile(const std::string& filepath);

public:
	Shader(const std::string& vertexShaderFilepath, const std::string& fragmentShaderFilepath);

	GLuint GetShaderProgram() const;

	void ActivateShaderProgram() const;
	void DeleteShaderProgram() const;

	GLuint GetUniformLocation(const std::string& name) const;
	void SetBool(const GLuint location, const bool val) const;
	void SetInt(const GLuint location, const int val) const;
	void SetVec3(const GLuint location, const glm::vec3 val) const;
	void SetVec4(const GLuint location, const glm::vec4 val) const;
	void SetMat4(const GLuint location, const glm::mat4& val) const;
};

#endif