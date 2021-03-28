#version 140

in vec3 position;
in vec2 texCoord;
in vec3 normal;
in vec3 tangent;
in vec3 biTangent;

out vec2 texCoord0;
out vec3 normal0;
out vec3 fragPos0;
out vec4 lightFragPos0;
out vec3 cameraPos0;
out mat3 tbnMatrix;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 lightVPMatrix;
uniform vec3 cameraPos;

void main()
{
	texCoord0 = texCoord;
	normal0 = normalize((modelMatrix * vec4(normal, 0.0)).xyz);
	fragPos0 = (modelMatrix * vec4(position, 1.0)).xyz;
	cameraPos0 = cameraPos;

	// Project vertices onto shadow map
	lightFragPos0 = (lightVPMatrix * vec4(fragPos0, 1.0));

	// Tangent and BiTangent in world space
	vec3 T = normalize(vec3(modelMatrix * vec4(tangent, 0.0)));
	vec3 B = normalize(vec3(modelMatrix * vec4(biTangent, 0.0)));
	tbnMatrix = mat3(T, B, normal0);

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}