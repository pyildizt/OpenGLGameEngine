#version 410

out vec4 FragColor;

uniform vec4 uniquePickingColor;

void main()
{
	FragColor = uniquePickingColor;
}