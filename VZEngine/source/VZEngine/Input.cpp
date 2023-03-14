#include "VZEngine/Input.h"
#include "VZEngine/Game.h"

using namespace std;

Input::Input()
{
	//assign the current keys by default
	KeyboardState = SDL_GetKeyboardState(NULL);
}

void Input::ProcessInput()
{
	SDL_Event PollEvent;

	while (SDL_PollEvent(&PollEvent))
	{
		switch (PollEvent.type)
		{
		case SDL_KEYDOWN:
			KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_KEYUP:
			KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_QUIT: // on close button pressed
			Game::GetGameInstance().CloseApp();
			break;
		default:
			break;
		}

	}
}

bool Input::IsKeyDown(SDL_Scancode key)
{
	//make sure the keyboard state is set
	if (KeyboardState == nullptr)
	{
		cout << "No keyboard state detected" << endl;
		return false;
	}
	return static_cast<bool>(KeyboardState[key]);
}
