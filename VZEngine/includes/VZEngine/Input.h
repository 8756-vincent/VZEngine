#pragma once
#include "SLD2/SDL.h"

class Input
{
public:
	Input();

	//detext the input of the user
	void ProcessInput();

	//detect if a specific key is down base on an sdl scancode
	//Hint* SDL_SCANCODE_KEY(SDL_SCANCODE_W)
	bool IsKeyDown(SDL_Scancode key);

private:
	const Uint8* KeyboardState;

};
