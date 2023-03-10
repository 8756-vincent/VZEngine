#pragma once
#include "VZEngine/CoreMinimal.h"

class Input;

class Game {
public:
	//get game instance or create one if it donest exist
	static Game& GetGameInstance();

	static void DestroyGameInstance();

	//start the game
	//load the window
	void Start(const char* WTitle, bool bFullscreen, int WWidth, int WHeight);

	//get precise delta time
	double GetDeltaTime() { return DeltaTime; }

	//gets less precise delta time
	float GetFDeltaTime() { return static_cast<float>(DeltaTime); }

	GraphicsEnginePtr GetGraphicEngine() { return Graphics; }

	//set the IsGameOver to true
	void CloseApp() { bIsGameOver = true; }

private:
	Game();
	~Game();

	//run the game loop
	void Run();

	//Handle the I/O stream
	void ProcessInput();

	//Handle Game Logic
	void Update();

	//Handle the 3D graphics drawing to the screen
	//clear and present each frame
	void Draw();

	//Handle anything that need to be deleted
	void CloseGame();

private:
	//boolean that ends the game
	bool bIsGameOver;

	//shared pointer to the graphics class
	GraphicsEnginePtr Graphics;

	//the time between each frame
	double DeltaTime;

	//read the input of the player
	Input* GameInput;

	//temp mesh var
	MeshPtr Poly2;
	MeshPtr Poly;
};