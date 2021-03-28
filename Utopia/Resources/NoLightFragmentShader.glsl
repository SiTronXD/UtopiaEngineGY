#version 140

in vec2 texCoord0;
in vec3 normal0;
in vec3 fragPos0;
in vec3 cameraPos0;

out vec4 fragColor;

uniform sampler2D diffuseTexture;

void main()
{
	fragColor = texture2D(diffuseTexture, texCoord0);
}