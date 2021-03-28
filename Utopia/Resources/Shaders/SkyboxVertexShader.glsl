#version 140

in vec3 position;

out vec3 fragPos0;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	fragPos0 = position;

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}