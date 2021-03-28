#version 140

in vec2 texCoord0;

out vec4 fragColor;

uniform sampler2D diffuseTexture;
uniform sampler2D renderedReflectanceTexture;
uniform sampler2D reflectanceTexture;

vec4 BlurReflectance(vec2 uv)
{
	vec3 currentCol = vec3(0.0);

	const int stepSize = 8;

	vec2 texelSize = 1.0 / textureSize(renderedReflectanceTexture, 0);

	// This works better, since it covers a bigger area within a smaller one :)))
	int numIterations = 0;
	for(int x = -stepSize; x <= stepSize; x++)
	{
		for(int y = -stepSize; y <= stepSize; y++)
		{
			float tempReflectanceAlpha = texture2D(reflectanceTexture, uv + vec2(x, y) * texelSize).a;
			vec4 tempCol = texture2D(renderedReflectanceTexture, uv + vec2(x, y) * texelSize);

			// Don't blur outside object
			if(tempReflectanceAlpha <= 0.0)
				continue;

			currentCol += tempCol.rgb;

			numIterations++;
		}
	}
	
	currentCol /= float(numIterations);


	float currentAlpha = 0.0;

	const int alphaStepSize = 16;

	// Blur alpha
	numIterations = 0;
	for(int x = -alphaStepSize; x <= alphaStepSize; x++)
	{
		for(int y = -alphaStepSize; y <= alphaStepSize; y++)
		{
			float tempReflectanceAlpha = texture2D(reflectanceTexture, uv + vec2(x, y) * texelSize).a;
			float tempAlpha = texture2D(renderedReflectanceTexture, uv + vec2(x, y) * texelSize).a;
			
			// Don't blur outside object
			if(tempReflectanceAlpha <= 0.2)
				continue;

			currentAlpha += tempAlpha;

			numIterations++;
		}
	}
	
	currentAlpha /= float(numIterations);

	return vec4(currentCol, currentAlpha);
}

void main()
{
	vec4 diffuseCol = texture2D(diffuseTexture, texCoord0);
	vec4 reflectCol = texture2D(renderedReflectanceTexture, texCoord0);
	vec4 reflectAmountCol = texture2D(reflectanceTexture, texCoord0);

	vec3 col = diffuseCol.rgb;

	// Mix with reflectance
	if(reflectAmountCol.a > 0.2)
	{
		vec4 blurReflectCol = BlurReflectance(texCoord0);
		col = mix(col, blurReflectCol.rgb, 0.4 * blurReflectCol.a + 0.2);
	}

	fragColor = vec4(col, 1.0);
}