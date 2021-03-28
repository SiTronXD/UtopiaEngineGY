#include "GYModel.h"

GYModel::GYModel(const std::string fileName, Transform & tr)
	: transform(tr)
{
	mesh = new Mesh(fileName);
}

GYModel::~GYModel()
{
	if (mesh != NULL)
		delete mesh;
}

void GYModel::Draw()
{
	if (mesh != NULL)
		mesh->Draw();
}

void GYModel::SetTransform(const Transform & transform)
{
	this->transform = transform;
}

Transform & GYModel::GetTransform()
{
	return transform;
}