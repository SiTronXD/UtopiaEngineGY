
#include "GYState.h"

GYState::GYState(Input& input)
	: GameState(input)
{
}

GYState::~GYState()
{
	delete spotLight;
	delete cube;
	delete cube2;
	delete cube3;
	delete skybox;
	delete plane;
	delete reflectObject;
	delete spectateController;
}

void GYState::Init()
{
	// Shader setup
	//shaders.push_back(new GYShader());
	shaders.push_back(new RealLightShader());
	shaders.push_back(new NoLightShader());

	currentShader = 0;

	textures.push_back(new Texture("./Resources/Terracotta_Base_Color.png", GL_LINEAR));
	textures.push_back(new Texture("./Resources/Terracotta_Normal.png", GL_LINEAR));
	textures.push_back(new Texture("./Resources/mud_leaves_diffuse.png"));
	textures.push_back(new Texture("./Resources/mud_leaves_normal.png"));
	textures.push_back(new Texture("./Resources/FullReflectance.png"));
	textures.push_back(new Texture("./Resources/NoReflectance.png"));
	textures.push_back(new Texture(10, 10, GL_LINEAR, GL_CLAMP, TextureType::COLOR));
	textures[6]->Clear(0.0f);

	mouseLookEnabled = true;

	glm::vec3 camPos = glm::vec3(0.3f, 0.2f, 1.0f);//glm::vec3(0.5f, 0.20f, 0.5f); 

	glm::vec3 camForward = glm::normalize(glm::vec3(0.0f) - camPos);

	camera = Camera(
		camPos,
		90.0f,
		(float)AppHandler::GetScreenWidth() / (float)AppHandler::GetScreenHeight(),
		0.1f,
		100.0f,
		camForward
	);

	counter = 0.0f;
	counter2 = 0.0f;

	glm::vec3 lightPos = glm::vec3(0.0f, 0.8f, 2.0f);
	spotLight = new SpotLight(lightPos, glm::vec3(0.0f), glm::ivec2(2048, 2048));

	// Cube
	Transform cubeTransform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
	TextureRegion top_tr(*textures[0], 0, 0, 1024, 1024);
	TextureRegion side_tr(*textures[0], 0, 0, 1024, 1024);
	TextureRegion bottom_tr(*textures[0], 0, 0, 1024, 1024);

	cube = new GYCube(*textures[0], *textures[1], 
		top_tr, side_tr, bottom_tr, 
		cubeTransform);

	// Cube 2
	Transform cube2Transform(glm::vec3(1.5f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

	cube2 = new GYCube(*textures[0], *textures[1],
		top_tr, side_tr, bottom_tr,
		cube2Transform);

	// Cube 3
	Transform cube3Transform(glm::vec3(-1.5f, -0.5f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

	cube3 = new GYCube(*textures[0], *textures[1],
		top_tr, side_tr, bottom_tr,
		cube3Transform);

	// Plane
	Transform planeTransform(glm::vec3(0.0f, -0.7f, 0.0f), glm::vec3(0.0f), glm::vec3(6.0f));

	TextureRegion tr(*textures[0], 0, 0, 1024, 1024);
	plane = new GYPlane(*textures[0+2], *textures[1+2], tr, planeTransform);

	// Sky box
	std::string skyboxFileNames[6] = {
		"./Resources/snowSkyboxRight.png",
		"./Resources/snowSkyboxLeft.png",
		"./Resources/snowSkyboxTop.png",
		"./Resources/snowSkyboxBottom.png",
		"./Resources/snowSkyboxFront.png",
		"./Resources/snowSkyboxBack.png"
	};
	skyboxTexture = new Texture(skyboxFileNames, GL_LINEAR);
	textures.push_back(skyboxTexture);

	Transform skyboxTransform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(100.0f));
	skybox = new GYInvertedCube(*textures[0], top_tr, side_tr, bottom_tr, skyboxTransform);

	// Reflect model
	Transform modelTransform(glm::vec3(1.5f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.7f));
	reflectObject = new GYModel("./Resources/monkey3.obj", modelTransform);

	// Other stuff
	spectateController = new PlayerSpectateController(&camera);

	input.SetLockMouse(true);

	// Diffuse screen texture
	screenTexture = new Texture(
		AppHandler::GetScreenWidth(), 
		AppHandler::GetScreenHeight(), 
		GL_LINEAR, 
		GL_CLAMP
	);
	textures.push_back(screenTexture);

	// Depth texture together with the diffuse screen texture
	worldDepthTexture = new Texture(
		AppHandler::GetScreenWidth(),
		AppHandler::GetScreenHeight(),
		GL_LINEAR,
		GL_CLAMP,
		TextureType::DEPTH
	);
	textures.push_back(worldDepthTexture);

	// Reflectance texture together with the diffuse screen texture
	screenReflectanceTexture = new Texture(
		AppHandler::GetScreenWidth(),
		AppHandler::GetScreenHeight(),
		GL_LINEAR,
		GL_CLAMP
	);
	textures.push_back(screenReflectanceTexture);

	// Shadow map
	this->CreateShadowMap();
	this->RenderShadowMap();

	// Textures used for ssr
	this->CreateReflectanceTextures();
}

void GYState::HandleInput(double dt)
{
	float spd = (float)(dt * 1.0);

	// Movement
	glm::vec2 walkDir(0.0f);
	walkDir.x = (float)(input.IsKeyDown(IK::D) - input.IsKeyDown(IK::A));
	walkDir.y = (float)(input.IsKeyDown(IK::W) - input.IsKeyDown(IK::S));
	spectateController->Move(walkDir, spd);

	// Levitation
	float levDir = (float)(input.IsKeyDown(IK::E) - input.IsKeyDown(IK::Q));
	spectateController->Levitate(levDir, spd);

	// Rotation
	if (mouseLookEnabled)
	{
		glm::vec2 lookDir(0.0f);
		lookDir = input.GetMouseDelta();
		lookDir.y *= -1.0f;
		spectateController->Rotate(lookDir, 0.07f);
	}

	// Switch current shader
	if (input.IsKeyJustPressed(IK::R))
	{
		currentShader++;
		if (currentShader > (int)(shaders.size()-1))
			currentShader = 0;
	}

	// Quit when clicking escape
	if (input.IsKeyJustPressed(IK::ESCAPE))
		AppHandler::Quit();
}

void GYState::Update(double dt)
{
	// Rotate cube
	transform = reflectObject->GetTransform();
	transform.GetRot().y = counter2;
	counter2 += (float)(dt * 20.0);


	//cube->SetTransform(transform);
	//reflectObject->SetTransform(transform);
}

void GYState::Draw()
{
	this->RenderShadowMap();
	this->RenderReflectanceTextures();
	this->RenderWorld(screenTexture);
	this->RenderWorld(worldDepthTexture);	// Not very optimized :/
	this->RenderToScreen();
}

void GYState::CreateShadowMap()
{
	// Create texture
	shadowMapTexture = new Texture(
		spotLight->GetShadowMapWidth(),
		spotLight->GetShadowMapHeight(),
		GL_LINEAR,
		GL_CLAMP,
		TextureType::DEPTH
	);
	textures.push_back(shadowMapTexture);

	// Set texture in spotlight
	spotLight->SetShadowMapTexture(shadowMapTexture);
}

void GYState::CreateReflectanceTextures()
{
	// Depth texture
	reflectanceDepthTexture = new Texture(
		AppHandler::GetScreenWidth(),
		AppHandler::GetScreenHeight(),
		GL_LINEAR,
		GL_CLAMP
	);
	textures.push_back(reflectanceDepthTexture);

	// Normal buffer
	normalBufferTexture = new Texture(
		AppHandler::GetScreenWidth(),
		AppHandler::GetScreenHeight(),
		GL_LINEAR,
		GL_CLAMP
	);
	textures.push_back(normalBufferTexture);

	// View space position buffer
	viewPosTexture = new Texture(
		AppHandler::GetScreenWidth(),
		AppHandler::GetScreenHeight(),
		GL_LINEAR,
		GL_CLAMP
	);
	textures.push_back(viewPosTexture);
}

void GYState::RenderShadowMap()
{
	// Set texture as target
	shadowMapTexture->BindAsRenderTarget();
	shadowMapTexture->Clear();

	// Render world to Shadow map
	shadowMapShader.Update(cube->GetTransform(), *spotLight);
	cube->Draw();

	shadowMapShader.Update(plane->GetTransform(), *spotLight);
	plane->Draw();
}

void GYState::RenderReflectanceTextures()
{
	// Render to reflectance depth texture		---------------------------
	reflectanceDepthTexture->BindAsRenderTarget();
	reflectanceDepthTexture->Clear(0.0f);

	// Skybox
	textures[5]->Bind(0);
	reflectanceAmountShader.Update(skybox->GetTransform(), camera);
	skybox->Draw(false);

	// Reflect object
	textures[5]->Bind(0);
	reflectanceAmountShader.Update(reflectObject->GetTransform(), camera);
	reflectObject->Draw();

	// Draw objects
	textures[5]->Bind(0);
	reflectanceAmountShader.Update(cube->GetTransform(), camera);
	cube->Draw(false);

	textures[4]->Bind(0);	// Render as white with max reflectance
	reflectanceAmountShader.Update(cube3->GetTransform(), camera);
	cube3->Draw(false);

	textures[5]->Bind(0);
	reflectanceAmountShader.Update(plane->GetTransform(), camera);
	plane->Draw(false);


	// Render to normal buffer texture			---------------------------
	normalBufferTexture->BindAsRenderTarget();
	normalBufferTexture->Clear(0.0f);

	normalBufferShader.Update(cube3->GetTransform(), camera);
	cube3->Draw();

	// Render to view position texture			---------------------------
	viewPosTexture->BindAsRenderTarget();
	viewPosTexture->Clear(0.0f);

	viewPosShader.Update(cube3->GetTransform(), camera);
	cube3->Draw();
}


void GYState::RenderWorld(Texture * currentRenderTarget)
{
	// Draw world to target texture
	currentRenderTarget->BindAsRenderTarget();
	currentRenderTarget->Clear();

	// Skybox
	if (currentShader == 0)
	{
		skyboxTexture->Bind(0, GL_TEXTURE_CUBE_MAP);
		skyboxShader.Update(skybox->GetTransform(), camera);
		skybox->Draw();
	}

	// Reflect object
	if (currentShader == 0)
	{
		skyboxTexture->Bind(0, GL_TEXTURE_CUBE_MAP);
		reflectShader.Update(reflectObject->GetTransform(), camera);
		reflectObject->Draw();
	}
	else
	{
		shaders[currentShader]->Update(reflectObject->GetTransform(), camera, *spotLight);
		reflectObject->Draw();
	}

	// Bind the same shadow map for all objects
	spotLight->GetShadowMapTexture().Bind(2);

	// Draw objects
	shaders[currentShader]->Update(cube->GetTransform(), camera, *spotLight);
	cube->Draw();

	shaders[currentShader]->Update(cube3->GetTransform(), camera, *spotLight);
	cube3->Draw();

	shaders[currentShader]->Update(plane->GetTransform(), camera, *spotLight);
	plane->Draw();
}

void GYState::RenderToScreen()
{
	// Bind reflectance texture
	screenReflectanceTexture->BindAsRenderTarget();
	screenReflectanceTexture->Clear(0.0f);

	// Draw screen space reflections
	screenTexture->Bind(0);
	worldDepthTexture->Bind(1);
	reflectanceDepthTexture->Bind(2);
	normalBufferTexture->Bind(3);

	renderReflectanceShader.Update(camera);
	screenQuad.Draw();


	// Bind window as target
	Display::BindAsRenderTarget();
	Display::Clear(0.0f, 0.0f, 0.0f, 1.0f);
	
	screenTexture->Bind(0);
	screenReflectanceTexture->Bind(1);
	if(currentShader == 0)					// No reflectance if it's the wrong current shader
		reflectanceDepthTexture->Bind(2); 
	else
		textures[6]->Bind(2);

	screenQuadShader.Update(camera); // Post-processing shader
	screenQuad.Draw();
}
