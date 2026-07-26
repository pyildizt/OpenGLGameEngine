#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader
{
private:
	GLuint shaderProgram{};

public:
	Shader();

	GLuint ShaderProgram() const;

	void ActivateShaderProgram() const;
	void DeleteShaderProgram() const;

	std::string readShaderFile(const std::string& filepath);

	GLuint GetUniformLocation(const std::string& name) const;
	void SetVec3(const GLuint location, const glm::vec3 val) const;
	void SetVec4(const GLuint location, const glm::vec4 val) const;
	void SetMat4(const GLuint location, const glm::mat4& val) const;
};

#endif