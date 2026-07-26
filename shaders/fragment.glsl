#version 410

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D myTexture;

void main()
{
	FragColor = texture(myTexture, TexCoord);
}