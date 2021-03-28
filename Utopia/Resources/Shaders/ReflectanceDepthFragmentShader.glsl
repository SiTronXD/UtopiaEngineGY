#version 140

in vec2 texCoord0;

out vec4 fragColor;

uniform sampler2D diffuseTexture;

// THIS SHADER DOESN'T HAVE ANYTHING TO DO WITH DEPTH 
// I realized the depth was useless, since I still render a depth texture! :))))
// I'm too lazy to change the name :^)
void main()
{
	float reflectAmount = texture2D(diffuseTexture, texCoord0).r;

	fragColor = vec4(reflectAmount);
}