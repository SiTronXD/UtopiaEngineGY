#version 140

in vec3 position;
in vec2 texCoord;
in vec3 normal;

out vec3 viewSpaceNormal0;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPos;

void main()
{
	// These two are apparently the same?
	//viewSpaceNormal0 = (inverse(transpose(viewMatrix * modelMatrix)) * vec4(normal, 0.0)).xyz;

	viewSpaceNormal0 = (viewMatrix * modelMatrix * vec4(normal, 0.0)).xyz;

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}