#version 140

//const vec3 lightPos = vec3(0.0, 0.0, 2.0);
//const vec3 lightPos = vec3(0.0, 0.8, 2.0);

in vec2 texCoord0;
in vec3 normal0;
in vec3 fragPos0;
in vec3 cameraPos0;
in mat3 tbnMatrix;

out vec4 fragColor;

uniform sampler2D diffuseTexture;
uniform sampler2D normalMap;

uniform vec3 lightPos;

vec3 normal;

float r(float val)
{
	float f = fract(val);

	return f >= 0.5 ? val + (1-f) : val - f;
}

float CalculateEdge()
{
	return r(
		pow(clamp(dot(-vec3(0, 0, 1), normal), 0.0, 1.0), 1.0)
	);
}

float CalculateDiffuseLight()
{
	vec3 lightDir = normalize(fragPos0 - lightPos);
	return clamp(dot(normal, -lightDir), 0.0, 1.0);
}

float CalculateSpecularLight()
{
	const int gloss = 16;
	const float intensity = 3;

	vec3 lightToFrag = normalize(fragPos0 - lightPos);
	vec3 camToFrag = normalize(fragPos0 - cameraPos0);
	vec3 reflectedDir = reflect(lightToFrag, normal);

	float specularValue = clamp(dot(reflectedDir, -camToFrag), 0.0, 1.0);

	float correctSide = dot(normal, -lightToFrag) < 0.0 ? 
		0.0 : 1.0;

	return pow(specularValue, gloss) * intensity * correctSide;
}

void main()
{
	// Calculate normal using normal map
	vec3 normalMapCol = texture(normalMap, texCoord0).rgb;
	normal = normalize(normalMapCol * 2.0 - 1.0); 
	normal = normalize(tbnMatrix * normal); 

	vec3 ambientLight = vec3(0.2, 0.2, 0.2);
	float diffuseLight = CalculateDiffuseLight();
	float specularLight = CalculateSpecularLight();

	vec3 finalLight = ambientLight + diffuseLight + specularLight;

	fragColor = texture2D(diffuseTexture, texCoord0) * vec4(finalLight, 1.0);
}