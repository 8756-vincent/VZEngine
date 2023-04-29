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

	//return the graphics engine default texture
	TexturePtr GetDefaultEngineTexture();

	//retrun the graphics engine dafault material
	MaterialPtr GetDefaultEngineMaterial();

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

	//remove a model from everywhere it needs to be removed
	void RemoveModelFromGame(ModelPtr& ModelToRemove);

private:
	//boolean that ends the game
	bool bIsGameOver;

	//shared pointer to the graphics class
	GraphicsEnginePtr Graphics;

	//the time between each frame
	double DeltaTime;

	//read the input of the player
	Input* GameInput;

	CollisionPtr CamCol;

	//temp mesh var
	ModelPtr Model2;
	
	ModelPtr Floor_1;

	ModelPtr Wall;
	ModelPtr Wall2;
	ModelPtr Wall3;
	ModelPtr Wall4;

	ModelPtr Corner1;
	ModelPtr Corner2;
	ModelPtr Corner3;
	ModelPtr Corner4;

	ModelPtr LightCube;

	ModelPtr HealthPickUp;
	ModelPtr Bomb;
};