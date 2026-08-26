#version 410

out vec4 FragColor;

in vec2 TexCoord;

uniform vec4 objectColor;
uniform sampler2D myTexture;
uniform bool useTexture;

void main()
{
	if (useTexture)
	{
		FragColor = texture(myTexture, TexCoord) * objectColor;
	}
	else
	{
		FragColor = objectColor;
	}
}