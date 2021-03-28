#version 140

in vec3 position;
in vec2 texCoord;

out vec2 uvCoords;

void main()
{
	uvCoords = texCoord;

	gl_Position = vec4(position, 1.0);
}