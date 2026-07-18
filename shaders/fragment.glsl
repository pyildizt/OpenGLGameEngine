#version 410

uniform vec3 vertexColor;

out vec4 FragColor;

void main()
{
	FragColor = vec4(vertexColor, 1.0f);
}