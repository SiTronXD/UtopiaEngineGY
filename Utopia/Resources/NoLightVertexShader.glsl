#version 140

in vec3 position;
in vec2 texCoord;
in vec3 normal;

out vec2 texCoord0;
out vec3 normal0;
out vec3 fragPos0;
out vec3 cameraPos0;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPos;

void main()
{
	texCoord0 = texCoord;
	normal0 = normalize((modelMatrix * vec4(normal, 0.0)).xyz);
	fragPos0 = (modelMatrix * vec4(position, 1.0)).xyz;
	cameraPos0 = cameraPos;

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}