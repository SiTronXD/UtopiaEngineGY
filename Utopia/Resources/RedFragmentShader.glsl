#version 140

in vec2 texCoord0;
in vec3 normal0;
in vec3 fragPos0;
in vec3 cameraPos0;
in mat3 tbnMatrix;

out vec4 fragColor;

uniform sampler2D diffuseTexture;
uniform sampler2D normalMap;

void main()
{
	fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}