#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <string>

class Texture
{
private:
	const std::string& filename;

	GLuint textureID;

	void SetDefaultParameters() const;

public:
	Texture(const std::string& textureFilename);

	const std::string& GetTextureFilename() const;
	
	GLuint GetTextureID() const;

	void BindTexture() const;
	void UnbindTexture() const;
	void DeleteTexture() const;

	void SetTextureParameter(GLenum parameterName, GLenum parameterVal) const;
};

#endif 