#version 140

in vec3 position;

out vec3 fragPos0;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	// View space position
	fragPos0 = (viewMatrix  * modelMatrix * vec4(position, 1.0)).xyz;

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}