#include "RayMarcherState.h"



RayMarcherState::RayMarcherState(Input& input)
	: GameState(input)
{
}


RayMarcherState::~RayMarcherState()
{
	delete shader;
	delete screenQuad;
}

void RayMarcherState::Init()
{
	shader = new RayMarcherShader();

	screenQuad = new ScreenQuad();

	time = 0;

	spherePositions.push_back(glm::vec3(0.0));
	spherePositions.push_back(glm::vec3(3.0));

	cameraPosition = glm::vec3(0.0, 0.0, -3.0);
	cameraDirection = glm::vec3(0.0);
}

void RayMarcherState::HandleInput(double dt)
{
	float playerSpeed = 5;
	float lookSpeed = 180;

	// Sprint
	if (input.IsKeyDown(IK::SHIFT_LEFT))
		playerSpeed = 20;

	// Movement
	if (input.IsKeyDown(IK::W))
	{
		cameraPosition.z += (float)(cos(glm::radians(cameraDirection.y)) * playerSpeed * dt);
		cameraPosition.x += (float)(sin(glm::radians(cameraDirection.y)) * playerSpeed * dt);
	}
	if (input.IsKeyDown(IK::S))
	{
		cameraPosition.z += (float)(-cos(glm::radians(cameraDirection.y)) * playerSpeed * dt);
		cameraPosition.x += (float)(-sin(glm::radians(cameraDirection.y)) * playerSpeed * dt);
	}
	if (input.IsKeyDown(IK::A))
	{
		cameraPosition.z += (float)( sin(glm::radians(cameraDirection.y)) * playerSpeed * dt);
		cameraPosition.x += (float)(-cos(glm::radians(cameraDirection.y)) * playerSpeed * dt);
	}
	if (input.IsKeyDown(IK::D))
	{
		cameraPosition.z += (float)(-sin(glm::radians(cameraDirection.y)) * playerSpeed * dt);
		cameraPosition.x += (float)( cos(glm::radians(cameraDirection.y)) * playerSpeed * dt);
	}

	// Levitate
	if (input.IsKeyDown(IK::E))
		cameraPosition.y += (float)( playerSpeed * dt);
	if (input.IsKeyDown(IK::Q))
		cameraPosition.y += (float)(-playerSpeed * dt);

	// Look
	if (input.IsKeyDown(IK::ARROW_UP))
		cameraDirection.x += (float)(lookSpeed * dt);
	if (input.IsKeyDown(IK::ARROW_DOWN))
		cameraDirection.x += (float)(-lookSpeed * dt);
	if (input.IsKeyDown(IK::ARROW_RIGHT))
		cameraDirection.y += (float)(lookSpeed * dt);
	if (input.IsKeyDown(IK::ARROW_LEFT))
		cameraDirection.y += (float)(-lookSpeed * dt);

	// Quit when clicking escape
	if (input.IsKeyJustPressed(IK::ESCAPE))
		AppHandler::Quit();
}

void RayMarcherState::Update(double dt)
{
	time += (float)dt;
}

void RayMarcherState::Draw()
{
	shader->Update(time, cameraPosition, cameraDirection, spherePositions);
	screenQuad->Draw();
}
