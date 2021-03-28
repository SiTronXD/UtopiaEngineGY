#version 140

in vec3 fragPos0;

out vec4 fragColor;

void main()
{
	// Output view space position as color
	fragColor = vec4(fragPos0, 1.0);
}