#include "Texture.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& textureFilename)
{
    // Create and bind texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Load texture image
    int width, height, nrChannels;
    unsigned char* imageData = stbi_load(textureFilename.c_str(), &width, &height, &nrChannels, 0);
    if (!imageData)
    {
        std::cout << "ERROR::TEXTURE::LOADING TEXTURE FAILED\n" << std::endl;
    }

    // Generate texture from image data
    GLenum format{};
    switch (nrChannels)
    {
    case 1:
        format = GL_RED;
        break;
    case 3:
        format = GL_RGB;
        break;
    case 4:
        format = GL_RGBA;
        break;
    default:
        throw std::runtime_error("Unsupported image format");
        break;
    }   

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Default parameters
    SetDefaultParameters();

    // Free image data
    stbi_image_free(imageData);
}

GLuint Texture::GetTextureID() const
{
	return textureID;
}

void Texture::BindTexture() const
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::UnbindTexture() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::DeleteTexture() const
{
	glDeleteTextures(1, &textureID);
}

void Texture::SetDefaultParameters() const
{
    // Set default texture wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::SetTextureParameter(GLenum parameterName, GLenum parameterVal) const
{
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, parameterName, parameterVal);
}