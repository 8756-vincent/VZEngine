#include "VZEngine/Game.h"
#include "VZEngine/Graphics/GraphicsEngine.h"
#include "VZEngine/Graphics/Mesh.h"
#include "VZEngine/Input.h"


Game& Game::GetGameInstance()
{
	static Game* GameInstance = new Game();
	return *GameInstance;
}

void Game::DestroyGameInstance()
{
	static Game* GameInstance = &GetGameInstance();

	delete GameInstance;
}

void Game::Start(const char* WTitle, bool bFullscreen, int WWidth, int WHeight)
{
	Graphics = make_shared<GraphicsEngine>();

	if (!Graphics->InitGE(WTitle, bFullscreen, WWidth, WHeight))
	{
		bIsGameOver = true;
	}

	Run();
}

Game::Game()
{
	cout << "Game Initialised!" << endl;

	Graphics = nullptr;
	bIsGameOver = false;
	GameInput = new Input();
}

Game::~Game()
{

	Graphics = nullptr;

	cout << "GameOver!" << endl;
}

void Game::Run()
{
	if (!bIsGameOver)
	{


		GameInput = new Input();

		ShaderPtr TextureShader = Graphics->CreateShader({
			L"Game/Shaders/TextureShader/TextureShader.svert",
			L"Game/Shaders/TextureShader/TextureShader.sfrag"
			});

		TexturePtr TCube = Graphics->CreateTexture("Game/Texture/multiCube.jpg");
		TexturePtr TGrid = Graphics->CreateTexture("Game/Texture/letterGrid.jpg");

		//create VAO
		Poly = Graphics->CreateSimpleMeshShape(GeometricShapes::Cube, TextureShader, { TCube });
		Poly2 = Graphics->CreateSimpleMeshShape(GeometricShapes::Cube, TextureShader, { TGrid });


		Poly->Transform.Location.x = 1.0f;
		Poly2->Transform.Location.x = -1.0f;

		//Poly->Transform.Location.x = 0.5f;
		//Poly->Transform.Scale = Vector3(0.5f);

	}

	while (!bIsGameOver)
	{
		//make sure we process what the user have done
		ProcessInput();

		//apply the logic based on the input and the game logic
		Update();

		//render base on the 2 above
		Draw();
	}

	//clean the game after it ends
	CloseGame();
}

void Game::ProcessInput()
{
	//run the input dectection for our game input
	GameInput->ProcessInput();
}

void Game::Update()
{
	//set delta time first always
	static double LastFrameTime = 0.0;
	//set the current time since the game has passed
	double CurrentFrameTime = static_cast<double>(SDL_GetTicks64());
	//find the time differences between the last and current frame
	double NewDeltaTime = CurrentFrameTime - LastFrameTime;
	//set delta time as seconds
	DeltaTime = NewDeltaTime / 1000.0;
	//update the last frame time for the next update
	LastFrameTime = CurrentFrameTime;

	Poly->Transform.Rotation.z += 50.0f * GetDeltaTime();
	Poly->Transform.Rotation.x += 50.0f * GetDeltaTime();
	Poly->Transform.Rotation.y += 50.0f * GetDeltaTime();
	
	Poly2->Transform.Rotation.z -= 50.0f * GetDeltaTime();
	Poly2->Transform.Rotation.x -= 50.0f * GetDeltaTime();
	Poly2->Transform.Rotation.y -= 50.0f * GetDeltaTime();

	Vector3 CameraInput = Vector3(0.0f);

	if(GameInput->IsKeyDown(SDL_SCANCODE_W)){
		CameraInput.z = 1.0f;
	}

	if(GameInput->IsKeyDown(SDL_SCANCODE_S)){
		CameraInput.z = -1.0f;
	}

	if (GameInput->IsKeyDown(SDL_SCANCODE_A)) {
		CameraInput.x = 1.0f;
	}

	if (GameInput->IsKeyDown(SDL_SCANCODE_D)) {
		CameraInput.x = -1.0f;
	}

	if (GameInput->IsKeyDown(SDL_SCANCODE_Q)) {
		CameraInput.y = -1.0f;
	}

	if (GameInput->IsKeyDown(SDL_SCANCODE_E)) {
		CameraInput.y = 1.0f;
	}/*
	if (GameInput->IsKeyDown(SDL_SCANCODE_R)) {
		CameraInput.FOV = 1.0f;
	}
	if (GameInput->IsKeyDown(SDL_SCANCODE_T)) {
		CameraInput.y = 1.0f;
	}
	if (GameInput->IsKeyDown(SDL_SCANCODE_Y)) {
		CameraInput.y = 1.0f;
	}*/

	CameraInput *= 1.0f * GetDeltaTime();

	Graphics->EngineDefaultCam += CameraInput;

	/*static double time = 0.0;

	time += DeltaTime;
	cout << time << endl;

	static int MoveUp = 1.0f;
	if (Tri->Transform.Location.y > 0.5f)
	{
		MoveUp = -1.0f;
	}
	
	if (Tri->Transform.Location.y < -0.5f)
	{
		MoveUp = 1.0f;
	}

	Tri->Transform.Location.y += (2.0f * MoveUp) * GetDeltaTime();*/
}

void Game::Draw()
{
	Graphics->Draw();
}

void Game::CloseGame()
{
	delete GameInput;
}
