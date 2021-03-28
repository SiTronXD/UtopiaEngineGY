#pragma once

#include "../Engine/Components/Mesh.h"
#include "../Engine/Components/Transform.h"

class GYModel
{
private:
	Transform transform;
	Mesh * mesh;

public:
	GYModel(const std::string fileName, Transform & tr);
	virtual ~GYModel();

	void Draw();

	void SetTransform(const Transform & transform);

	Transform & GetTransform();
};