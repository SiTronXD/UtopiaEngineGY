#version 140

in vec3 position;
in vec2 texCoord;

out vec2 texCoord0;
out vec3 cameraPos0;
out mat4 projectionMatrix0;
out mat4 invertedProjectionMatrix0;

uniform mat4 projectionMatrix;
uniform vec3 cameraPos;

void main()
{
	texCoord0 = texCoord;
	cameraPos0 = cameraPos;
	projectionMatrix0 = projectionMatrix;
	invertedProjectionMatrix0 = inverse(projectionMatrix);


	gl_Position = vec4(position, 1.0);
}