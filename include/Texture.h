#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <string>

class Texture
{
private:
	GLuint textureID;

	void SetDefaultParameters() const;

public:
	Texture(const std::string& textureFilename);
	
	GLuint TextureID() const;

	void BindTexture() const;
	void UnbindTexture() const;
	void DeleteTexture() const;

	void SetTextureParameter(GLenum parameterName, GLenum parameterVal) const;
};

#endif 