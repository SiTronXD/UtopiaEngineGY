#include "PlayerSpectateController.h"

PlayerSpectateController::PlayerSpectateController(Camera* camera)
	: camera(camera)
{
}

PlayerSpectateController::~PlayerSpectateController()
{
	
}

void PlayerSpectateController::Move(glm::vec2 dir, float speed)
{
	glm::vec3 positionDelta(0.0f);
	positionDelta += camera->GetForward() * dir.y;
	positionDelta += camera->GetLeft() * dir.x;

	camera->MovePosition(positionDelta * speed);
}

void PlayerSpectateController::Levitate(float dir, float speed)
{
	glm::vec3 positionDelta(0.0f, dir, 0.0f);

	camera->MovePosition(positionDelta * speed);
}

void PlayerSpectateController::Rotate(glm::vec2 dirDelta, float speed)
{
	camera->Rotate(dirDelta * speed);
}