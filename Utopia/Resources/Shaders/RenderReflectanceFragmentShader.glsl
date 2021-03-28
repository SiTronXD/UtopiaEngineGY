#version 140

in vec2 texCoord0;
in vec3 cameraPos0;
in mat4 projectionMatrix0;
in mat4 invertedProjectionMatrix0;

out vec4 fragColor;

uniform sampler2D diffuseTexture;
uniform sampler2D depthTexture;
uniform sampler2D reflectanceTexture;
uniform sampler2D normalBufferTexture;
uniform sampler2D viewPosTexture;

float GetLinearDepth(float currentDepth)
{
	const float far = 100.0;
	const float near = 0.1;

	float z = currentDepth * 2.0 - 1.0;

	return (2.0 * near * far) / (far + near - z * (far - near)) / far;
}

vec3 HashRand(vec2 uv)
{
	uv = fract(uv * vec2(654.345, 751.324));
	uv += dot(uv, uv*vec2(422.32, 565.32));

	return normalize(fract(vec3(uv.x, uv.y, uv.x*uv.y*642.412) * vec3(123.654)) * 2.0 - 1.0);
}

vec4 GetReflectedColor(vec2 uv, float depth, vec3 currentNormal)
{
	// From Screen space, to Clip space, to View space
	vec4 viewPos = vec4(uv, depth, 1.0);
	viewPos = viewPos * 2.0 - 1.0;

	viewPos = invertedProjectionMatrix0 * viewPos;
	viewPos.xyz /= viewPos.w;	

	// Short random offset
	vec3 reflectOffset = HashRand(uv)*0.08;

	// Create direction and reflect
	vec3 viewDir = normalize(viewPos.xyz);	// fragment position - camera position
	vec3 reflectDir = normalize(reflect(viewDir, currentNormal)) + reflectOffset;
	vec4 projCoords = vec4(0.0);

	const vec4 noResultCol = vec4(0.0);


	// Step along ray
	vec3 p = viewPos.xyz;
	for(int i = 0; i < 100; i++)
	{
		p += reflectDir * 0.05;

		// Project
		projCoords = projectionMatrix0 * vec4(p, 1.0);
		projCoords.xyz /= projCoords.w;
		projCoords = projCoords * 0.5 + 0.5;

		// Outside frustum
		if(projCoords.x < 0.0 || projCoords.x > 1.0 ||
			projCoords.y < 0.0 || projCoords.y > 1.0 ||
			projCoords.z < 0.0 || projCoords.z > 1.0)
			return noResultCol;

		float currentDepth = texture2D(depthTexture, projCoords.xy).r;

		// Hit something
		if(projCoords.z >= currentDepth)
		{
			// Went too far
			if(abs(GetLinearDepth(projCoords.z) - GetLinearDepth(currentDepth)) >= 0.05)
				return noResultCol;
			else
			{
				vec3 foundCol = texture2D(diffuseTexture, projCoords.xy).rgb;

				return vec4(foundCol, 1.0);
			}
		}
	}

	// Point is still within frustum, so this will be the fallback
	return vec4(texture2D(diffuseTexture, projCoords.xy).rgb, 1.0);

	//return noResultCol;
}

void main()
{
	vec3 diffuseCol = texture2D(diffuseTexture, texCoord0).rgb;
	vec3 depthCol = texture2D(depthTexture, texCoord0).rgb;
	vec4 reflectanceCol = texture2D(reflectanceTexture, texCoord0);
	vec3 normalCol = normalize((texture2D(normalBufferTexture, texCoord0).xyz * 2.0) - 1.0); // -1 to 1

	// Reflectance
	if(reflectanceCol.a > 0.0)
	{
		vec4 rayTracedCol = GetReflectedColor(texCoord0, depthCol.r, normalCol);

		// Found traced color
		if(rayTracedCol.a > 0.0)
			fragColor = vec4(rayTracedCol.rgb, 1.0);
	}
	else // Default color
		fragColor = vec4(0.0);
}