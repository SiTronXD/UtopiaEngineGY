#version 140

in vec2 texCoord0;
in vec3 normal0;
in vec3 fragPos0;
in vec4 lightFragPos0;
in vec3 cameraPos0;
in mat3 tbnMatrix;

out vec4 fragColor;

uniform sampler2D diffuseTexture;
uniform sampler2D normalMap;
uniform sampler2D shadowMap;

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
	vec3 lightDir = fragPos0 - lightPos;
	return clamp(dot(normal, -lightDir), 0.0, 1.0);
}

float CalculateSpecularLight()
{
	vec3 lightToFrag = normalize(fragPos0 - lightPos);
	vec3 camToFrag = normalize(fragPos0 - cameraPos0);
	vec3 reflectedDir = reflect(lightToFrag, normal);

	float sVal = clamp(dot(reflectedDir, -camToFrag), 0.0, 1.0);

	float lightAndNormal = dot(lightToFrag, normal) >= 0.0 ? 
		0.0 : 1.0;

	// REMEMBER: Could be slow
	return pow(sVal, 10) * 3 * lightAndNormal;
}

float CalculateShadowMapVisibility()
{
	// Project coordinates
	vec3 projCoords = lightFragPos0.xyz / lightFragPos0.w;
	projCoords = projCoords * 0.5 + 0.5;

	// Outside shadow frustum
	if( projCoords.x < 0.0 || projCoords.x > 1.0 || 
		projCoords.y < 0.0 || projCoords.y > 1.0 ||
		projCoords.z < 0.0 || projCoords.z > 1.0)
		return 1.0;

	// Get depth
	float currentDepth = projCoords.z;
	
	// Offset depth
	vec3 lightToFrag = normalize(fragPos0 - lightPos);
	float depthOffset = max(0.00002 * (1.0 - dot(normal, lightToFrag)), 0.000001);

	// Blur shadow edge
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);

	const int stepSize = 2;
	for(int x = -stepSize; x <= stepSize; x++)	// Horizontal blur
	{
		float shadowMapDepth = texture(shadowMap, projCoords.xy + vec2(x, 0.0) * texelSize).r;

		shadow += currentDepth - depthOffset < shadowMapDepth ? 1.0 : 0.0;
	}
	for(int y = -stepSize; y <= stepSize; y++)	// Vertical blur
	{
		float shadowMapDepth = texture(shadowMap, projCoords.xy + vec2(0.0, y) * texelSize).r;

		shadow += currentDepth - depthOffset < shadowMapDepth ? 1.0 : 0.0;
	}
	
	// Average
	shadow /= (2.0 * stepSize + 1.0) * 2.0;

	// Compare
	return min(shadow + 0.2, 1.0);
}

void main()
{
	// Calculate normal using normal map
	normal = texture(normalMap, texCoord0).rgb; 
	normal = normalize(normal * 2.0 - 1.0); 
	normal = normalize(tbnMatrix * normal); 

	//normal = normal0;

	float ambientLight = 0.2;
	float diffuseLight = CalculateDiffuseLight();
	float specularLight = CalculateSpecularLight();

	float finalLight = (ambientLight + diffuseLight + specularLight);
	finalLight *= CalculateShadowMapVisibility();

	fragColor = texture2D(diffuseTexture, texCoord0) * finalLight;
}