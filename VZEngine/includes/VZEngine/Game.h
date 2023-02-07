#pragma once
#include "VZEngine/Graphics/GraphicsEngine.h"
#include <iostream>

using namespace std;

class Game {
public:
	//get game instance or create one if it donest exist
	static Game& GetGameInstance();

	static void DestroyGameInstance();

	//start the game
	//load the window
	void Start(const char* WTitle, bool bFullscreen, int WWidth, int WHeight);

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

	GraphicsEngine* Graphics;
};