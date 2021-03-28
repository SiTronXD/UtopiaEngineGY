#pragma once

#include "../Engine/GameState.h"
#include "../Engine/Display.h"

#include "../CustomShaderPrograms/GYShader.h"
#include "../CustomShaderPrograms/RealLightShader.h"
#include "../CustomShaderPrograms/NoLightShader.h"
#include "../CustomShaderPrograms/GYScreenQuadShader.h"
#include "../CustomShaderPrograms/ShadowMapShader.h"
#include "../CustomShaderPrograms/SkyboxShader.h"
#include "../CustomShaderPrograms/ReflectShader.h"
#include "../CustomShaderPrograms/ReflectanceDepthShader.h"
#include "../CustomShaderPrograms/NormalBufferShader.h"
#include "../CustomShaderPrograms/ViewPosShader.h"
#include "../CustomShaderPrograms/RenderReflectanceShader.h"
#include "../Engine/Lights/SpotLight.h"
#include "../Entities/GYCube.h"
#include "../Entities/GYInvertedCube.h"
#include "../Entities/GYPlane.h"
#include "../Entities/GYModel.h"
#include "../Entities/PlayerSpectateController.h"
#include "../Engine/ScreenQuad.h"

class GameState;
class PlayerSpectateController;
class Input;

class GYState :
	public GameState
{
private:
	Camera camera;
	Transform transform;

	GYScreenQuadShader screenQuadShader;
	ShadowMapShader shadowMapShader;
	SkyboxShader skyboxShader;
	ReflectShader reflectShader;
	ReflectanceDepthShader reflectanceAmountShader;
	NormalBufferShader normalBufferShader;
	ViewPosShader viewPosShader;
	RenderReflectanceShader renderReflectanceShader;

	ScreenQuad screenQuad;
	Texture * screenTexture;
	Texture * screenReflectanceTexture;
	Texture * worldDepthTexture;
	Texture * shadowMapTexture;
	Texture * skyboxTexture;
	Texture * reflectanceDepthTexture;
	Texture * normalBufferTexture;
	Texture * viewPosTexture;

	SpotLight * spotLight;

	GYCube* cube;
	GYCube* cube2;
	GYCube* cube3;
	GYPlane* plane;
	GYInvertedCube* skybox;
	GYModel * reflectObject;

	PlayerSpectateController* spectateController;

	int currentShader;

	float counter;
	float counter2;

	bool mouseLookEnabled;

public:
	GYState(Input& input);
	virtual ~GYState();

	virtual void Init();
	virtual void HandleInput(double dt);
	virtual void Update(double dt);
	virtual void Draw();

	void CreateShadowMap();
	void CreateReflectanceTextures();
	void RenderShadowMap();
	void RenderReflectanceTextures();
	void RenderWorld(Texture * target);
	void RenderToScreen();
};