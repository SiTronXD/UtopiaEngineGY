#version 140

in vec3 fragPos0;

out vec4 fragColor;

uniform samplerCube skyboxTexture;

void main()
{
	fragColor = texture(skyboxTexture, fragPos0);
}