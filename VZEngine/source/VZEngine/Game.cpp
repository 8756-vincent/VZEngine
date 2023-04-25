#include "VZEngine/Game.h"
#include "VZEngine/Graphics/GraphicsEngine.h"
#include "VZEngine/Graphics/Model.h"
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

MaterialPtr Game::GetDefaultEngineMaterial()
{
	return Graphics->DefaultEngineMaterial;
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
		//create an input class to detect input
		GameInput = new Input();

		//create a shader
		ShaderPtr TextureShader = Graphics->CreateShader({
			L"Game/Shaders/TextureShader/TextureShader.svert",
			L"Game/Shaders/TextureShader/TextureShader.sfrag"
			});
		
		//texture
		TexturePtr TCube = Graphics->CreateTexture("Game/Texture/multiCube.jpg");
		TexturePtr TGrid = Graphics->CreateTexture("Game/Texture/concrete.jpg");

		//create the material
		MaterialPtr MCube = make_shared<Material>();
		MaterialPtr MGrid = make_shared<Material>();

		//assign the base colour of the materials using the textures
		MCube->BaseColour.TextureV3 = TCube;
		MGrid->BaseColour.TextureV3 = TGrid;


		//create VAO
		Model = Graphics->ImportModel("Game/Model/PrimitiveModels/Cube.fbx", TextureShader);
		//set materials of the models
		Model->SetMaterialBySlot(0, MCube);
		//transform
		Model->Transform.Location = Vector3(0.0f, 1.0f, 0.0f);
		Model->AddCollisionToModel(Vector3(1.5f));

		//Sphere
		Model2 = Graphics->ImportModel("Game/Model/PrimitiveModels/Sphere.fbx", TextureShader);
		//set material
		Model2->SetMaterialBySlot(0, MGrid);
		Model2->GetMaterialBySlot(0)->EmissiveColour.MultiplierV3 = Vector3(2.0f);
		//Transform
		Model2->Transform.Location = Vector3(-0.0f, -1.0f, 0.0f);
		Model2->AddCollisionToModel(Vector3(2.0f));

		//import custom meshes
		Wall = Graphics->ImportModel("Game/Model/damaged-wall/source/SM_Wall_Damaged.obj", TextureShader);
		Wall2 = Graphics->ImportModel("Game/Model/damaged-wall/source/SM_Wall_Damaged.obj", TextureShader);
		//texture
		TexturePtr TWall = Graphics->CreateTexture("Game/Model/damaged-wall/textures/T_Wall_Damaged_BC.png");
		//material
		MaterialPtr MWall = make_shared<Material>();
		MWall->BaseColour.TextureV3 = TWall;
		Wall->SetMaterialBySlot(1, MWall);
		Wall2->SetMaterialBySlot(1, MWall);
		//transform
		Wall->Transform.Scale = Vector3(0.05f);
		Wall->Transform.Rotation.y = 90.0f;
		Wall->Transform.Location = Vector3(10.0f, -2.0f, 0.0f);
		//add Collision
		Wall->AddCollisionToModel(Vector3(1.0f, 4.0f, 10.0f), Vector3(0.0f, 2.0f, 0.0f));

		Wall2->Transform.Scale = Vector3(0.05f);
		Wall2->Transform.Rotation.y = 90.0f;
		Wall2->Transform.Location = Vector3(15.0f, -2.0f, 0.0f);
		//add Collision
		Wall2->AddCollisionToModel(Vector3(1.0f, 4.0f, 10.0f), Vector3(0.0f, 2.0f, 0.0f));

		//create
		HealthPickUp = Graphics->ImportModel("Game/Model/HealthPickUp/source/FirstAidBox.fbx", TextureShader);
		//Texture
		TexturePtr THealthPickup = Graphics->CreateTexture("Game/Model/HealthPickUp/textures/FirstAid_D.png");
		TexturePtr SHealthPickup = Graphics->CreateTexture("Game/Model/HealthPickUp/textures/FirstAid_R.png");
		//Health Pick up material
		MaterialPtr MHealthPickup = make_shared<Material>();
		MHealthPickup->BaseColour.TextureV3 = THealthPickup;
		MHealthPickup->SpecularColour.TextureV3 = SHealthPickup;
		HealthPickUp->SetMaterialBySlot(0, MHealthPickup);
		//Transform
		HealthPickUp->Transform.Scale = Vector3(0.005f);
		HealthPickUp->Transform.Rotation.x = 90.0f;
		HealthPickUp->Transform.Rotation.z = 90.0f;
		HealthPickUp->Transform.Location = Vector3(5.0f, 0.0f, 5.0f);

		//Bomb craete
		Bomb = Graphics->ImportModel("Game/Model/free-bomb/source/LP_bomb_uv_triangl.fbx", TextureShader);	
		//Texture
		TexturePtr TBomb = Graphics->CreateTexture("Game/Model/free-bomb/textures/bombBaseColor.png");
		TexturePtr SBomb = Graphics->CreateTexture("Game/Model/free-bomb/textures/bombMetallic.png");
		//Material
		MaterialPtr MBomb = make_shared<Material>();
		MBomb->BaseColour.TextureV3 = TBomb;
		MBomb->SpecularColour.TextureV3 = SBomb;
		Bomb->SetMaterialBySlot(0, MBomb);
		//transform
		Bomb->Transform.Location = Vector3(5.0f, 5.0f, -5.0f);

		//LightCube create
		LightCube = Graphics->ImportModel("Game/Model/PrimitiveModels/Cube.fbx", TextureShader);
		//Set Material
		LightCube->GetMaterialBySlot(0)->EmissiveColour.MultiplierV3 = Vector3(2.0f);
		LightCube->Transform.Location = Vector3(10.0f, 5.0f, 5.0f);


		cout << "Press H for help menu" << endl;
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
	//Moving left and right Sphere
	static float LocationShift = 2.0f;
	if (Model2->Transform.Location.z > 10.0f)
	{
		LocationShift = -2.0f;
	}
	if (Model2->Transform.Location.z < 1.0f) {
		LocationShift = 2.0f;
	}
	Model2->Transform.Location.z += LocationShift * GetDeltaTime();


	//Growing and shrinking Health
	static Vector3 ScaleChange = Vector3(0.005f);
	if (HealthPickUp->Transform.Scale.x > 0.03f)
	{
		ScaleChange = Vector3(-0.005f);
	}
	if (HealthPickUp->Transform.Scale.x < 0.004f)
	{
		ScaleChange = Vector3(0.005f);
	}
	HealthPickUp->Transform.Scale += ScaleChange * GetFDeltaTime();


	//input
	Vector3 CameraInput = Vector3(0.0f);
	CDirection CamDirections = Graphics->EngineDefaultCam->GetDirection();

	if (GameInput->IsKeyDown(SDL_SCANCODE_W)) {
		CameraInput += CamDirections.Forward;
	}

	if (GameInput->IsKeyDown(SDL_SCANCODE_S)) {
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
	if (GameInput->ScrollDelta > 0 && NewFOV != 100) {
		if (NewFOV < 100)
		{
			NewFOV++;
		}
		cout << "Current FOV: " << NewFOV << endl;
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
	//float Speed = Graphics->EngineDefaultCam->GetCameraData().Speed;
	if (GameInput->IsKeyDown(SDL_SCANCODE_LSHIFT)) {
		Graphics->EngineDefaultCam->Speed(10.0f);
		cout << "Sprting" << endl;
	}
	else {
		Graphics->EngineDefaultCam->Speed(5.0f);
	}
	if (GameInput->IsKeyDown(SDL_SCANCODE_LCTRL)) {
		Graphics->EngineDefaultCam->Speed(0.8f);
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
		Graphics->EngineDefaultCam->RotatePitch(-GameInput->MouseYDelta);
		Graphics->EngineDefaultCam->RotateYaw(GameInput->MouseXDelta);
		GameInput->ShowCursor(false);
	}
	else
	{
		GameInput->ShowCursor(true);
	}

	//setting new Camera settings
	Graphics->EngineDefaultCam->FOV(NewFOV);
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


	//transform
	if (Model != nullptr)
	{
		Model->Transform.Rotation.z += 50.0f * GetDeltaTime();
		Model->Transform.Rotation.x += 50.0f * GetDeltaTime();
		Model->Transform.Rotation.y += 50.0f * GetDeltaTime();
	}
	if (Model2 != nullptr)
	{
		Model2->Transform.Rotation.z -= 50.0f * GetDeltaTime();
		Model2->Transform.Rotation.x -= 50.0f * GetDeltaTime();
		Model2->Transform.Rotation.y -= 50.0f * GetDeltaTime();
	}


	


	Graphics->EngineDefaultCam->Update();


	//collision
	CollisionPtr CamCol = Graphics->EngineDefaultCam->GetCameraCollision();

	
	if (Wall != nullptr && CamCol->IsOverLapping(*Wall->GetCollision()))
	{
		RemoveModelFromGame(Wall2);
	}
}

void Game::Draw()
{
	Graphics->ClearGraphics();
	Graphics->Draw();

	//CollisionPtr CamCol = Graphics->EngineDefaultCam->GetCameraCollision());

	//if (Wall != nullptr && Wall2->GetCollision()->IsOverLapping(*Wall->GetCollision()))
	//{
	//	Wall2->GetCollision()->DebugDraw(Vector3(0.0f, 255.0f, 0.0f));
	//}
	//else
	//{
	//	Wall2->GetCollision()->DebugDraw(Vector3(255.0f, 0.0f, 0.0f));
	//}

	//if (Wall != nullptr && CamCol->IsOverLapping(*Wall->GetCollision()))
	//{
	//	CamCol->DebugDraw(Vector3(0.0f, 255.0f, 0.0f));
	//}
	//else
	//{
	//	CamCol->DebugDraw(Vector3(255.0f, 0.0f, 0.0f));
	//}

	Graphics->PresentGraphics();
}

void Game::CloseGame()
{
	delete GameInput;
}

void Game::RemoveModelFromGame(ModelPtr& ModelToRemove)
{
	//remove from the graphics engine
	Graphics->RemoveModel(ModelToRemove);

	//change the reference to nullptr and remove from the game
	ModelToRemove = nullptr;
}
