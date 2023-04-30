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
		////create VAO
		//Model = Graphics->ImportModel("Game/Model/PrimitiveModels/Cube.fbx", TextureShader);
		////set materials of the models
		//Model->SetMaterialBySlot(0, MCube);
		////transform
		//Model->Transform.Location = Vector3(0.0f, 1.0f, 0.0f);
		//Model->AddCollisionToModel(Vector3(1.5f));


		Model = Graphics->ImportModel("Game/Model/shiba//shiba/shiba.FBX", TextureShader);
		//set material
		TexturePtr TShaiba = Graphics->CreateTexture("Game/Model/shiba/textures/default_Base_Color.png");
		MaterialPtr MShaiba = make_shared<Material>();
		MShaiba->BaseColour.TextureV3 = TShaiba;
		Model->SetMaterialBySlot(0, MShaiba);
		//Transform
		Model->Transform.Location = Vector3(-0.0f, -1.0f, -8.0f);
		Model->Transform.Rotation.x = -90.0f;
		Model->AddCollisionToModel(Vector3(2.0f));

		//Shiba 2
		Model2 = Graphics->ImportModel("Game/Model/shiba//shiba/shiba.FBX", TextureShader);
		//set material
		Model2->SetMaterialBySlot(0, MShaiba);
		//Transform
		Model2->Transform.Location = Vector3(-0.0f, -1.0f, 0.0f);
		Model2->Transform.Rotation.x = -90.0f;
		Model2->AddCollisionToModel(Vector3(2.0f));

		//import custom meshes
		//create
		HealthPickUp = Graphics->ImportModel("Game/Model/HealthPickUp/FirstAidBox.fbx", TextureShader);
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
		HealthPickUp->AddCollisionToModel(Vector3(1.2f), Vector3(0.0f));

		//Bomb create
		Bomb = Graphics->ImportModel("Game/Model/free-bomb/LP_bomb_uv_triangl.fbx", TextureShader);	
		//Texture
		TexturePtr TBomb = Graphics->CreateTexture("Game/Model/free-bomb/textures/bombBaseColor.png");
		TexturePtr SBomb = Graphics->CreateTexture("Game/Model/free-bomb/textures/bombMetallic.png");
		//Material
		MaterialPtr MBomb = make_shared<Material>();
		MBomb->BaseColour.TextureV3 = TBomb;
		MBomb->SpecularColour.TextureV3 = SBomb;
		Bomb->SetMaterialBySlot(0, MBomb);
		//transform
		Bomb->Transform.Scale = Vector3(0.5f);
		Bomb->Transform.Rotation.x = -90.0f;
		Bomb->Transform.Location = Vector3(-10.0f, -1.0f, -5.0f);
		Bomb->AddCollisionToModel(Vector3(2.0f));

		Goal = Graphics->ImportModel("Game/Model/cheap-fusion-coil/FusionCoil.obj", TextureShader);
		TexturePtr TGoal = Graphics->CreateTexture("Game/Model/free-bomb/Diffuse.jpg");
		MaterialPtr MGoal = make_shared<Material>();
		MGoal->BaseColour.TextureV3 = TGoal;
		Goal->SetMaterialBySlot(1, MGoal);
		Goal->Transform.Location = Vector3(20.0f, -1.0f, 5.0f);
		Goal->AddCollisionToModel(Vector3(2.0f));


		//LightCube create
		LightCube = Graphics->ImportModel("Game/Model/PrimitiveModels/Cube.fbx", TextureShader);
		//Set Material
		LightCube->GetMaterialBySlot(0)->EmissiveColour.MultiplierV3 = Vector3(2.0f);
		LightCube->Transform.Location = Vector3(0.0f, 50.0f, 0.0f);

		LightSphere = Graphics->ImportModel("Game/Model/PrimitiveModels/Sphere.fbx", TextureShader);
		//Set Material
		LightSphere->Transform.Location = Vector3(-12.7f, 8.5f, -0.8f);
		LightSphere->GetMaterialBySlot(0)->EmissiveColour.MultiplierV3 = Vector3(2.0f,2.0f,0.0f);

		LightSphere2 = Graphics->ImportModel("Game/Model/PrimitiveModels/Sphere.fbx", TextureShader);
		//Set Material
		LightSphere2->Transform.Location = Vector3(20.0f, 8.0f, 0.0f);

		//Floor
		Floor_1 = Graphics->ImportModel("Game/Model/floor-material/plane.fbx", TextureShader);		
		TexturePtr TFloor = Graphics->CreateTexture("Game/Model/floor-material/textures/Floortile1AO.png");
		MaterialPtr MFloor = make_shared<Material>();
		MFloor->BaseColour.TextureV3 = TFloor;
		Floor_1->SetMaterialBySlot(0, MFloor);
		//Transform
		Floor_1->Transform.Scale = Vector3(0.125f);
		Floor_1->Transform.Location = Vector3(0.0f, -2.5f, 0.0f);
		Floor_1->AddCollisionToModel(Vector3(50.0f,0.1f,50.0f));


		//Wall
		Wall = Graphics->ImportModel("Game/Model/damaged-wall/wall/SM_Wall_Damaged.obj", TextureShader);
		Wall2 = Graphics->ImportModel("Game/Model/damaged-wall/wall/SM_Wall_Damaged.obj", TextureShader);
		Wall3 = Graphics->ImportModel("Game/Model/damaged-wall/wall/SM_Wall_Damaged.obj", TextureShader);
		Wall4 = Graphics->ImportModel("Game/Model/damaged-wall/wall/SM_Wall_Damaged.obj", TextureShader);
		TexturePtr TWall = Graphics->CreateTexture("Game/Model/damaged-wall/textures/T_Wall_Damaged_BC.png");
		MaterialPtr MWall = make_shared<Material>();
		MWall->BaseColour.TextureV3 = TWall;
		Wall->SetMaterialBySlot(1, MWall);
		Wall2->SetMaterialBySlot(1, MWall);
		Wall3->SetMaterialBySlot(1, MWall);
		Wall4->SetMaterialBySlot(1, MWall);
		//transform
		Wall->Transform.Scale = Vector3(0.15f);
		Wall->Transform.Rotation.y = 90.0f;
		Wall->Transform.Location = Vector3(25.9f, -2.2f, 0.0f);
		//add Collision
		Wall->AddCollisionToModel(Vector3(3.0f, 12.0f, 30.0f), Vector3(0.0f, 6.0f, 0.0f));

		Wall2->Transform.Scale = Vector3(0.15f);
		Wall2->Transform.Rotation.y = -90.0f;
		Wall2->Transform.Location = Vector3(-25.1f, -2.2f, 0.0f);
		//add Collision
		Wall2->AddCollisionToModel(Vector3(3.0f, 12.0f, 30.0f), Vector3(0.0f, 6.0f, 0.0f));

		Wall3->Transform.Scale = Vector3(0.15f);
		Wall3->Transform.Location = Vector3(0.0f, -2.2f, -25.1f);
		//add Collision
		Wall3->AddCollisionToModel(Vector3(30.0f, 12.0f, 3.0f), Vector3(0.0f, 6.0f, 0.0f));
		
		Wall4->Transform.Scale = Vector3(0.15f);
		Wall4->Transform.Location = Vector3(0.0f, -2.2f, 25.1f);
		//add Collision
		Wall4->AddCollisionToModel(Vector3(30.0f, 12.0f, 3.0f), Vector3(0.0f, 6.0f, 0.0f));

		Corner1 = Graphics->ImportModel("Game/Model/PrimitiveModels/Cube.fbx", TextureShader);
		//set materials of the models
		Corner1->SetMaterialBySlot(0, MCube);
		//transform
		Corner1->Transform.Scale = Vector3(2.0f);
		Corner1->Transform.Location = Vector3(21.0f, -0.7f, -21.0f);
		Corner1->AddCollisionToModel(Vector3(2.0f));

		Corner2 = Graphics->ImportModel("Game/Model/PrimitiveModels/Cube.fbx", TextureShader);
		//set materials of the models
		Corner2->SetMaterialBySlot(0, MCube);
		//transform
		Corner2->Transform.Scale = Vector3(2.0f);
		Corner2->Transform.Location = Vector3(21.0f, -0.7f, 21.0f);
		Corner2->AddCollisionToModel(Vector3(2.0f));

		Corner3 = Graphics->ImportModel("Game/Model/PrimitiveModels/Cube.fbx", TextureShader);
		//set materials of the models
		Corner3->SetMaterialBySlot(0, MCube);
		//transform
		Corner3->Transform.Scale = Vector3(2.0f);
		Corner3->Transform.Location = Vector3(-21.0f, -0.7f, -21.0f);
		Corner3->AddCollisionToModel(Vector3(2.0f));

		Corner4 = Graphics->ImportModel("Game/Model/PrimitiveModels/Cube.fbx", TextureShader);
		//set materials of the models
		Corner4->SetMaterialBySlot(0, MCube);
		//transform
		Corner4->Transform.Scale = Vector3(2.0f);
		Corner4->Transform.Location = Vector3(-21.0f, -0.7f, 21.0f);
		Corner4->AddCollisionToModel(Vector3(2.0f));

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

	//input
	Vector3 CameraInput = Vector3(0.0f);
	CDirection CamDirections = Graphics->EngineDefaultCam->GetDirection();
	CamCol = Graphics->EngineDefaultCam->GetCameraCollision();

	if (GameInput->IsKeyDown(SDL_SCANCODE_W)) {
		if (CamCol->IsOverLapping(*Wall->GetCollision()))
		{
			CameraInput += -CamDirections.Forward;
		}
		else if (CamCol->IsOverLapping(*Wall2->GetCollision()))
		{
			CameraInput += -CamDirections.Forward;
		}
		else if (CamCol->IsOverLapping(*Wall3->GetCollision()))
		{
			CameraInput += -CamDirections.Forward;
		}
		else if (CamCol->IsOverLapping(*Wall4->GetCollision()))
		{
			CameraInput += -CamDirections.Forward;
		}
		else
		{
			CameraInput += CamDirections.Forward;
		}
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
		Graphics->EngineDefaultCam->Speed(20.0f);
	}
	else {
		Graphics->EngineDefaultCam->Speed(5.0f);
	}
	if (GameInput->IsKeyDown(SDL_SCANCODE_LCTRL)) {
		Graphics->EngineDefaultCam->Speed(0.8f);
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
	if (Graphics->GetHP() <=0)
	{
		cout << endl << "You died, we'll get them next time." << endl;
		SDL_Delay(2000);
		bIsGameOver = true;
		return;
	}

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

	//Moving left and right shiba
	static float LocationShift = 2.0f;
	CamCol = Graphics->EngineDefaultCam->GetCameraCollision();

	static float movement = -2.0f;
	if (Model != nullptr)
	{		
		if (Model->Transform.Location.z > -1.0f)
		{
			movement = -2.0f;
			Model->Transform.Rotation.z = 180.0f;
		}
		if (Model->Transform.Location.z < -20.0f) {
			movement = 2.0f;
			Model->Transform.Rotation.z = 0.0f;
		}
		Model->Transform.Location.z += movement * GetDeltaTime();

		if (CamCol->IsOverLapping(*Model->GetCollision()))
		{
			Graphics->calHP(-0.5f);
			cout << endl << "You got ambushed lost 0.5hp. Remaining: " << Graphics->GetHP() << endl;
		}

	}

	if (Model2 != nullptr)
	{
		if (Model2->Transform.Location.z > 10.0f)
		{
			LocationShift = -2.0f;
			Model2->Transform.Rotation.z = 180.0f;
		}
		if (Model2->Transform.Location.z < 1.0f) {
			LocationShift = 2.0f;
			Model2->Transform.Rotation.z = 0.0f;
		}
		Model2->Transform.Location.z += LocationShift * GetDeltaTime();

		if (CamCol->IsOverLapping(*Model2->GetCollision()))
		{
			Graphics->calHP(-0.5f);
			cout << endl << "You got ambushed lost 0.5hp. Remaining: " << Graphics->GetHP() << endl;
			
		}
	}
	//transform
	if (Corner1 != nullptr)
	{
		Corner1->Transform.Rotation.z += 50.0f * GetDeltaTime();
		Corner1->Transform.Rotation.x += 50.0f * GetDeltaTime();
		Corner1->Transform.Rotation.y += 50.0f * GetDeltaTime();
	}
	if (Corner2 != nullptr)
	{
		Corner2->Transform.Rotation.z -= 50.0f * GetDeltaTime();
		Corner2->Transform.Rotation.x -= 50.0f * GetDeltaTime();
		Corner2->Transform.Rotation.y -= 50.0f * GetDeltaTime();
	}
	if (Corner3 != nullptr)
	{
		Corner3->Transform.Rotation.z += 50.0f * GetDeltaTime();
		Corner3->Transform.Rotation.x += 50.0f * GetDeltaTime();
		Corner3->Transform.Rotation.y += 50.0f * GetDeltaTime();
	}
	if (Corner4 != nullptr)
	{
		Corner4->Transform.Rotation.z -= 50.0f * GetDeltaTime();
		Corner4->Transform.Rotation.x -= 50.0f * GetDeltaTime();
		Corner4->Transform.Rotation.y -= 50.0f * GetDeltaTime();
	}




	//Growing and shrinking Health
	static Vector3 ScaleChange = Vector3(0.005f);
	if (HealthPickUp != nullptr)
	{
		if (HealthPickUp->Transform.Scale.x > 0.03f)
		{
			ScaleChange = Vector3(-0.005f);
		}
		if (HealthPickUp->Transform.Scale.x < 0.004f)
		{
			ScaleChange = Vector3(0.005f);
		}
		HealthPickUp->Transform.Scale += ScaleChange * GetFDeltaTime();

		if (CamCol->IsOverLapping(*HealthPickUp->GetCollision()))
		{
			RemoveModelFromGame(HealthPickUp);
			Graphics->calHP(50.f);
			cout<< endl << "You Gain 50hp. " << endl;
		}
		
	}

	Graphics->EngineDefaultCam->Update();
	
	if (Bomb != nullptr && CamCol->IsOverLapping(*Bomb->GetCollision()))
	{
		RemoveModelFromGame(Bomb);
		Graphics->calHP(-25.f);
		cout << endl << "You got ambushed lost 25hp. Remaining: " << Graphics->GetHP() << endl;
	}
	
	if (Goal != nullptr && CamCol->IsOverLapping(*Goal->GetCollision()))
	{
		RemoveModelFromGame(Goal);
		cout << endl << "You got the item you can close the game now " << endl;
		cout << endl << "You Finished in:  "<< SDL_GetTicks64()/1000 << " Seconds" << endl;
	}
	
}

void Game::Draw()
{
	Graphics->ClearGraphics();
	Graphics->Draw();
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
