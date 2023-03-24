#include "VZEngine/Input.h"
#include "VZEngine/Game.h"

using namespace std;

Input::Input()
{
	//assign the current keys by default
	KeyboardState = SDL_GetKeyboardState(NULL);
	MouseXDelta = MouseYDelta = 0;
	ScrollDelta = 0;
}

void Input::ProcessInput()
{
	//reset the delta each frame
	MouseXDelta = MouseYDelta = 0;
	ScrollDelta = 0;


	SDL_Event PollEvent;

	while (SDL_PollEvent(&PollEvent))
	{
		switch (PollEvent.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			//PollEvent.button.button gets the indext of the mouse button pressed
			SetMouseButtonStates(PollEvent.button.button, true);
			break;
		case SDL_MOUSEBUTTONUP:
			SetMouseButtonStates(PollEvent.button.button, false);
			break;
		case SDL_MOUSEMOTION:
			OnMouseMove(PollEvent.motion);
			break;
		case SDL_MOUSEWHEEL:
			OnMouseScroll(PollEvent.wheel);
			break;
		case SDL_KEYDOWN:			
			switch (PollEvent.key.keysym.sym)
			{
			case SDLK_ESCAPE: // on close button pressed
				Game::GetGameInstance().CloseApp();
				break;
			case SDLK_h: // on close button pressed
				HelpMenu();
				break;
			default:
				break;
			}
			
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

void Input::HelpMenu()
{
	cout << "        Help Menu" << endl;
	cout << "1. WASD to Move" << endl;
	cout << "2. QE to go up and down" << endl;
	cout << "3. Hold RMB to look around" << endl;
	cout << "4. Mouse Scroll Up increase FOV" << endl;
	cout << "5. Mouse Scroll Down decrease FOV" << endl;
	cout << "6. R to reset FOV" << endl;
	cout << "7. LShift to go faster" << endl;
	cout << "8. LCtrl to go slow walk/speed" << endl << endl;
}

bool Input::IsMouseButtonDown(MouseButtons Button)
{
	return MouseButtonStates[Button];
}


void Input::SetMouseButtonStates(Uint8 ButtonIndex, bool CurrentState)
{
	MouseButtonStates[ButtonIndex] = CurrentState;
}

void Input::OnMouseMove(SDL_MouseMotionEvent& MEvent)
{
	// the mouse position
	MouseX = MEvent.x;
	MouseY = MEvent.y;

	//movement of the mouse based on the last position
	//the relative moovement
	MouseXDelta += MEvent.xrel;
	MouseYDelta += MEvent.yrel;
}

void Input::OnMouseScroll(SDL_MouseWheelEvent& MSEvent)
{
	//increase the delta relative to how much was scrolled
	ScrollDelta += MSEvent.preciseY;
}
