#version 140

in vec2 uvCoords;

out vec4 fragColor;

const float PI = 3.141592;
const float screenAspectRatio = 1280.0/720.0;
const float Deg2Rad = 1.0 / 180.0 * PI;
const float minRayDist = 0.1;
const float fov = 45.0f;

uniform float time;

uniform vec3 cameraPos;
uniform vec3 cameraDir;
uniform vec3 spherePositions[2];

struct Ray
{
	vec3 position;
	vec3 direction;
	vec3 currentNormal;
	float currentDistance;
	float currentDistanceToObject;
	float currentMinDistanceToObject;
	float currentMaterial;
};

Ray CreateRay(vec3 pos, vec3 dir)
{
	Ray r;
	r.position = pos;
	r.direction = dir;
	r.currentNormal = vec3(0.0);
	r.currentDistance = minRayDist;
	r.currentMaterial = 0.0;
	r.currentDistanceToObject = 0.0;
	r.currentMinDistanceToObject = 9999;

	return r;
}

struct ObjectInfo 
{
	float dist;
	float material;
	vec3 normal;
};

ObjectInfo GetDistPlane(vec3 pos)
{
	float offset = 1.5;
	float amp = 0.24;

	float kPosX = 1;
	float kPosZ = 1;

	offset = 0;
	amp = 1;

	return ObjectInfo(
		abs(pos.y + 1),
		offset + amp*(sin(pos.x * kPosX) + sin(pos.z * kPosZ)),
		vec3(0.0, 1.0, 0.0)
	);
}

ObjectInfo GetDistSphere(vec3 pos, vec3 spherePos)
{
	//vec3 spherePos = vec3(sin(time)*3, 0.0,-1.0);
	float sphereRadius = 1.0;

	return ObjectInfo(
		length(pos - spherePos) - sphereRadius, 
		1.0,
		normalize(pos - spherePos)
	);
}

void main()
{
	// Normalize UV coordinates
	vec2 normUV = vec2(uvCoords.x, 1-uvCoords.y);
	normUV = normUV - 0.5;
	normUV.x *= screenAspectRatio;

	// Create ray
	float hAngle = (cameraDir.y + normUV.x * fov) * Deg2Rad;
	float vAngle = (cameraDir.x + normUV.y * fov) * Deg2Rad;

	vec3 rayPos = cameraPos;
	vec3 rayDirection = vec3(
		sin(hAngle) * cos(vAngle),
		sin(vAngle),
		cos(hAngle) * cos(vAngle)
	);

	//rayDirection = normalize(rayDirection);

	Ray ray = CreateRay(rayPos, rayDirection);

	// Ray marching
	float minDist = 0.0;
	for(int i = 0; i < 250; i++)
	{
		minDist = 999.0;
		vec3 currentPos = ray.position + ray.direction*ray.currentDistance;

		// Find the "best" object
		ObjectInfo currentInfo;

		// Spheres
		for(int j = 0; j < spherePositions.length(); j++)
		{
			ObjectInfo tempInfo = GetDistSphere(currentPos, spherePositions[j]);
			
			if(tempInfo.dist < minDist)
			{
				minDist = tempInfo.dist;
				currentInfo = tempInfo;
			}
		}

		// Planes
		for(int j = 0; j < 1; j++)
		{
			ObjectInfo tempInfo = GetDistPlane(currentPos);

			if(tempInfo.dist < minDist)
			{
				minDist = tempInfo.dist;
				currentInfo = tempInfo;
			}
		}

		// Step along the ray
		ray.currentDistance += minDist;
		ray.currentDistanceToObject = currentInfo.dist;

		if(minDist < ray.currentMinDistanceToObject)
			ray.currentMinDistanceToObject = minDist;

		// Hit something
		if(ray.currentDistanceToObject <= 0.01)
		{
			ray.currentMaterial = currentInfo.material;
			ray.currentNormal = currentInfo.normal;
			break;
		}
	}

	// Check material
	vec4 col = vec4(0.0, 0.0, 0.0, 1.0);
	if(ray.currentMaterial <= 0.0)
	{
		col = vec4(0.0, 0.0, 0.0, 1.0);
	}
	else if(ray.currentMaterial <= 1.0)
	{
		col = vec4(1.0, 1.0, 1.0, 1.0);
	}
	else if(ray.currentMaterial <= 2.0)
	{
		float v = fract(ray.currentMaterial);

		col = vec4(1.0, 0.0, 0.0, 1.0) * v;
	}

	vec4 shadeCol = col * 
		clamp(dot(ray.currentNormal, -vec3(sin(time*3), -1.0, cos(time*3))), 0.3, 1.0);
	
	
	// Glow effect
	float glowDist = 0.3;
	if(ray.currentDistanceToObject > 0.01)
		shadeCol = vec4(0.0, 1.0, 0.0, 1.0) * (glowDist - clamp(ray.currentMinDistanceToObject, 0.0, glowDist)) / glowDist;
	

	fragColor = shadeCol;
}