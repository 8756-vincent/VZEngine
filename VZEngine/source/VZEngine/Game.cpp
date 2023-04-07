#include "VZEngine/Game.h"
#include "VZEngine/Graphics/GraphicsEngine.h"
#include "VZEngine/Graphics/Mesh.h"
#include "VZEngine/Input.h"
#include "VZEngine/Graphics/Camera.h"
#include "VZEngine/Graphics/Material.h"


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

TexturePtr Game::GetDefaultEngineTexture()
{
	return Graphics->DefaultEngineTexture;
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
		TexturePtr TSus = Graphics->CreateTexture("Game/Texture/sus.png");
		TexturePtr TGrid = Graphics->CreateTexture("Game/Texture/concrete.jpg");
		TexturePtr TTransparent = Graphics->CreateTexture("Game/Texture/transparent.png");

		//create the material
		MatherialPtr MConcrete = make_shared<Material>();
		MatherialPtr MGrid = make_shared<Material>();

		//assign the base colour of the materials using the textures
		MConcrete->BaseColour = TCube;
		MGrid->BaseColour = TGrid;


		//create VAO
		Poly = Graphics->CreateSimpleMeshShape(GeometricShapes::Cube, TextureShader, MConcrete);
		Poly2 = Graphics->CreateSimpleMeshShape(GeometricShapes::Cube, TextureShader, MGrid);

		cout << "Press H for help" << endl;
		Poly->Transform.Location = Vector3(0.0f,1.0f,0.0f);
		Poly2->Transform.Location = Vector3(-0.0f, -1.0f, 0.0f);
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

	CDirection CamDirections = Graphics->EngineDefaultCam->GetDirection();
	float Speed = Graphics->EngineDefaultCam->GetCameraData().Speed;

	if(GameInput->IsKeyDown(SDL_SCANCODE_W)){
		CameraInput += CamDirections.Forward;
	}

	if(GameInput->IsKeyDown(SDL_SCANCODE_S)){
		CameraInput += -CamDirections.Forward;
	}

	if (GameInput->IsKeyDown(SDL_SCANCODE_A)) {
		CameraInput += -CamDirections.Right;
	}

	if (GameInput->IsKeyDown(SDL_SCANCODE_D)) {
		CameraInput += CamDirections.Right;
	}

	//up
	if (GameInput->IsKeyDown(SDL_SCANCODE_Q)) {
		CameraInput += CamDirections.Up;
	}

	//down
	if (GameInput->IsKeyDown(SDL_SCANCODE_E)) {
		CameraInput += -CamDirections.Up;
	}

	//FOV
	float NewFOV = Graphics->EngineDefaultCam->GetCameraData().FOV;
	if (GameInput->ScrollDelta > 0 && NewFOV !=100) {
		if (NewFOV < 100)
		{
			NewFOV++;
		}
		cout << "Current FOV: " << NewFOV<< endl;
	}
	if (GameInput->ScrollDelta < 0 && NewFOV != 0) {
		if (NewFOV > 0)
		{
			NewFOV--;
		}	
		cout << "Current FOV: " << NewFOV << endl;
	}
	if (GameInput->IsKeyDown(SDL_SCANCODE_R) && NewFOV != 70)
	{
		NewFOV = 70.0f;
		cout << "Restting FOV: " << NewFOV << endl;
	}


	//Speed Shift	
	if (GameInput->IsKeyDown(SDL_SCANCODE_LSHIFT)) {
		Speed = 4.0f;
		cout << "Sprting" << endl;
	}
	if (GameInput->IsKeyDown(SDL_SCANCODE_LCTRL)) {
		Speed = 0.5f;
		cout << "Slow Walking" << endl;
	}


	//Gravity-applies to camera only
	Vector3 gravity = Vector3(0.0f, 0.05f, 0.0f);

	if (GameInput->GetGravity())
	{
		//Speed = 0.5f;
		CameraInput += -(CamDirections.Up + gravity);
	}

	Graphics->EngineDefaultCam->AddMovementInput(CameraInput);

	//Holding right mouse button
	if (GameInput->IsMouseButtonDown(MouseButtons::RIGHT)) {
		Graphics->EngineDefaultCam->RotatePitch(-GameInput->MouseYDelta * GetFDeltaTime());
		Graphics->EngineDefaultCam->RotateYaw(GameInput->MouseXDelta * GetFDeltaTime());
		GameInput->ShowCursor(false);
	}
	else
	{
		GameInput->ShowCursor(true);
	}

	//setting new FOV
	Graphics->EngineDefaultCam->FOV(NewFOV);
}

void Game::Draw()
{
	Graphics->Draw();
}

void Game::CloseGame()
{
	delete GameInput;
}
