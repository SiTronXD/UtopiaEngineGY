#include "TestState.h"

TestState::TestState(Input& input)
	: GameState(input)
{
}

TestState::~TestState()
{
	delete spectateController;
}

void TestState::Init()
{
	/*
	// Triangle
	vertices[0] = Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.5f));
	vertices[1] = Vertex(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec2(0.5f, 0.0f));
	vertices[2] = Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.5f));

	unsigned int indices[] = { 0, 1, 2 };
	*/

	vertices[0] = Vertex(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec2(0.5f, 0.0f));
	vertices[1] = Vertex(glm::vec3(0.0f, -0.5f, 1.0f), glm::vec2(0.0f, 1.0f));
	vertices[2] = Vertex(glm::vec3(0.87f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f));
	vertices[3] = Vertex(glm::vec3(-0.87f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f));

	unsigned int indices[] = 
	{  
		1, 2, 0,
		2, 3, 0,
		3, 1, 0,
		1, 3, 2
	};

	meshes.push_back(new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]),
		indices, sizeof(indices) / sizeof(indices[0])));
	meshes.push_back(new Mesh("./Resources/monkey3.obj"));

	/*
	shaders.push_back(new Shader(
		"./Resources/NoLightVertexShader.glsl",
		"./Resources/NoLightFragmentShader.glsl"
	));
	*/

	textures.push_back(new Texture("./Resources/jah.png"));
	textures.push_back(new Texture("./Resources/ObamasLastName.png"));

	camera = Camera(
		glm::vec3(0, 0, -3), 
		90.0f, 
		(float)Game::GetScreenWidth() / (float)Game::GetScreenHeight(), 
		0.01f, 
		500.0f
	);

	counter = 0.0f;
	counter2 = 0.0f;

	spectateController = new PlayerSpectateController(&camera);

	input.SetLockMouse(true);
}

void TestState::HandleInput(double dt)
{
	float spd = (float)(dt * 4.0);

	// Movement
	glm::vec2 walkDir(0.0f);
	walkDir.x = (float)(input.IsKeyDown(IK::D) - input.IsKeyDown(IK::A));
	walkDir.y = (float)(input.IsKeyDown(IK::W) - input.IsKeyDown(IK::S));
	spectateController->Move(walkDir, spd);

	// Levitation
	float levDir = (float)(input.IsKeyDown(IK::E) - input.IsKeyDown(IK::Q));
	spectateController->Levitate(levDir, spd);

	// Rotation
	glm::vec2 lookDir(0.0f);
	lookDir = input.GetMouseDelta();
	lookDir.y *= -1.0f;
	spectateController->Rotate(lookDir, 0.1f);

	// Quit when clicking escape
	if (input.IsKeyJustPressed(IK::ESCAPE))
		AppHandler::Quit();
}

void TestState::Update(double dt)
{
	transform.GetRot().y = 180.0f;

	float sinCounter = sinf(counter);
	float cosCounter = cosf(counter);

	//transform.GetPos().x = sinCounter;
	//transform.GetPos().z = cosCounter;

	counter2 += (float)(dt * 180.0);

	transform.GetRot().y = counter2;

	counter += (float)(dt * 3.0);
}

void TestState::Draw()
{
	/* (to avoid errors)
	shaders[0]->Bind();
	textures[0]->Bind(0);
	shaders[0]->Update(transform, camera);
	meshes[0]->Draw();
	*/
}