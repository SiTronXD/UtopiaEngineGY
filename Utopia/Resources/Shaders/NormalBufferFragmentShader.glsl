#version 140

in vec3 viewSpaceNormal0;

out vec4 fragColor;

void main()
{
	// Keep color from 0 to 1
	vec3 normalColor = viewSpaceNormal0.xyz * 0.5 + 0.5;

	fragColor = vec4(normalColor, 1.0);
}