#include "VZEngine/Game.h"

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
	Graphics = new GraphicsEngine();

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
}

Game::~Game()
{
	cout << "GameOver!" << endl;
}

void Game::Run()
{
<<<<<<< Updated upstream
=======
	if (!bIsGameOver)
	{
		Graphics->CreateShader({
			L"Game/Shaders/SimpleShader/SimpleShader.svert",
			L"Game/Shaders/SimpleShader/SimpleShader.sfrag"
			});

		//create VAO
		Graphics->CreateVAO(GeometricShapes::Triangle);
		Graphics->CreateVAO(GeometricShapes::Polygon);
		//Graphics->CreateVAO(GeometricShapes::Circle);
	}

>>>>>>> Stashed changes
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
	
}

void Game::Update()
{
}

void Game::Draw()
{
}

void Game::CloseGame()
{
}
