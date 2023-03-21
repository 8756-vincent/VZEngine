#include "VZEngine/Game.h"
#include "VZEngine/Graphics/GraphicsEngine.h"
#include "VZEngine/Graphics/Mesh.h"
#include "VZEngine/Input.h"
#include "VZEngine/Graphics/Camera.h"


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


		Poly->Transform.Location = Vector3(1.0f,0.0f,0.0f);
		Poly2->Transform.Location = Vector3(1.0f, 0.0f, 0.0f);
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

	//set speed to frame
	CameraInput *= 5.0f *GetDeltaTime();

	Vector3 NewLocation = Graphics->EngineDefaultCam->GetTransform().Location += CameraInput;

	if (GameInput->IsMouseButtonDown(MouseButtons::RIGHT)) {
		Graphics->EngineDefaultCam->RotatePitch(-GameInput->MouseYDelta * GetDeltaTime() * 50.0f);
		Graphics->EngineDefaultCam->RotateYaw(GameInput->MouseXDelta * GetDeltaTime() * 50.0f);
	}
	Graphics->EngineDefaultCam->Translate(NewLocation);


	//float FOVInput = 0.0f;
	////FOV 
	//if (GameInput->IsKeyDown(SDL_SCANCODE_R)) {
	//	//Graphics->EngineDefaultCam->GetCameraData().FOV = 70.0f;
	//	cout << "Resetting FOV to " << Graphics->EngineDefaultCam->GetCameraData().FOV << endl;
	//}

	//if (GameInput->IsKeyDown(SDL_SCANCODE_T)) {
	//	FOVInput = 1.0f;
	//	cout << "Increasing FOV by 1 now it's " << Graphics->EngineDefaultCam->GetCameraData().FOV << endl;
	//}

	//if (GameInput->IsKeyDown(SDL_SCANCODE_Y)) {
	//	FOVInput = -1.0f;
	//	cout << "Decreasing FOV by 1 now it's " << Graphics->EngineDefaultCam->GetCameraData().FOV << endl;
	//}

	//float Sprint = 1.0f;
	////Shift
	//if (GameInput->IsKeyDown(SDL_SCANCODE_LSHIFT)) {
	//	Sprint = 4.0f;
	//	cout << "Sprting" << endl;
	//}
	//if (GameInput->IsKeyDown(SDL_SCANCODE_LCTRL)) {
	//	Sprint = 0.5f;
	//	cout << "Crouching" << endl;
	//}
	//if (GameInput->IsKeyDown(SDL_SCANCODE_SPACE)) {		
	//	if (Graphics->EngineDefaultCam.y >= 0)
	//	{
	//		CameraInput.y = -100.0f;
	//		cout << "Jumping" << endl;
	//	}		
	//}


}

void Game::Draw()
{
	Graphics->Draw();
}

void Game::CloseGame()
{
	delete GameInput;
}
