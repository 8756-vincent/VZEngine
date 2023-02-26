#include "VZEngine/Game.h"
#include "VZEngine/Graphics/GraphicsEngine.h"

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
		Graphics->CreateShader({
			L"Game/Shaders/SimpleShader/SimpleShader.svert",
			L"Game/Shaders/SimpleShader/SimpleShader.sfrag"
			});

		//create VAO
		Graphics->CreateVAO(GeometricShapes::Triangle);
		Graphics->CreateVAO(GeometricShapes::Polygon);
		Graphics->CreateVAO(GeometricShapes::Circle);
		Graphics->CreateVAO(GeometricShapes::Circle20);
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
	SDL_Event PollEvent;

	while (SDL_PollEvent(&PollEvent))
	{
		switch (PollEvent.type)
		{
		case SDL_QUIT: // on close button pressed
			bIsGameOver = true;
			break;
		default:
			break;
		}

	}
}

void Game::Update()
{

}

void Game::Draw()
{
	Graphics->Draw();
}

void Game::CloseGame()
{

}
