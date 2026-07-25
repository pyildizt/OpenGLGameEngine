#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>

class Shader
{
private:
	GLuint shaderProgram{};

public:
	Shader();

	void SetShaderProgram(GLuint newShaderProgram);
	GLuint GetShaderProgram() const;

	void ActivateShaderProgram() const;
	void DeleteShaderProgram() const;

	std::string readShaderFile(const std::string& filepath);
};

#endif