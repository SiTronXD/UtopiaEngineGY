#pragma once

#include "../Components/Transform.h"
#include "../Components/Mesh.h"
#include "../Components/Texture.h"
#include "../TextureRegion.h"
#include "../Components/Shader.h"
#include "../Debugging/Log.h"

class Renderable
{
protected:
	Mesh* mesh;

	Texture& texture;

	Transform transform;

public:
	Renderable(Texture& texture);
	virtual ~Renderable();

	virtual void Draw(bool bindOwnTexture = true);

	void SetTransform(const Transform& transform);

	Transform & GetTransform();
};