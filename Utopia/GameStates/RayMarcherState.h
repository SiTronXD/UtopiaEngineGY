#pragma once

#include "../CustomShaderPrograms/RayMarcherShader.h"
#include "../Engine/GameState.h"
#include "../Engine/ScreenQuad.h"
#include "../Engine/Debugging/Log.h"

class RayMarcherState :
	public GameState
{
private:
	RayMarcherShader* shader;
	ScreenQuad* screenQuad;

	std::vector<glm::vec3> spherePositions;

	glm::vec3 cameraPosition;
	glm::vec3 cameraDirection;

	float time;

public:
	RayMarcherState(Input& input);
	virtual ~RayMarcherState();

	virtual void Init();
	virtual void HandleInput(double dt);
	virtual void Update(double dt);
	virtual void Draw();
};