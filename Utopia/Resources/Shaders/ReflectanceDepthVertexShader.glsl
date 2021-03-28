#version 140

in vec3 position;
in vec2 texCoord;

out vec2 texCoord0;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPos;

void main()
{
	texCoord0 = texCoord;

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}