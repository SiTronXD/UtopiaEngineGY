#version 140

in vec3 fragPos0;
in vec3 normal0;

out vec4 fragColor;

uniform vec3 camPos;

uniform samplerCube skyboxTexture;

void main()
{
	vec3 camToFrag = normalize(fragPos0 - camPos);
	vec3 reflectedDir = reflect(camToFrag, normal0);
	fragColor = texture(skyboxTexture, reflectedDir);
}