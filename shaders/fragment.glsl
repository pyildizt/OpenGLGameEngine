#version 410

out vec4 FragColor;

in vec3 myColor;
in vec2 TexCoord;

uniform vec3 vertexColor;
uniform sampler2D myTexture;

void main()
{
	FragColor = vec4(vertexColor, 1.0f) * texture(myTexture, TexCoord);
}