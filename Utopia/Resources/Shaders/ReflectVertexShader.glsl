#version 140

in vec3 position;
in vec2 texCoord;
in vec3 normal;

out vec3 fragPos0;
out vec3 normal0;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	fragPos0 = (modelMatrix * vec4(position, 1.0)).xyz;
	normal0 = (modelMatrix * vec4(normal, 0.0)).xyz;

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}