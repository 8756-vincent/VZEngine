#include "VZEngine/Input.h"
#include "VZEngine/Game.h"

using namespace std;

Input::Input()
{
	//assign the current keys by default
	KeyboardState = SDL_GetKeyboardState(NULL);
	MouseXDelta = MouseYDelta = 0;
	ScrollDelta = 0;
	freeCam = true;
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
			case SDLK_g: // on close button pressed
				if (!GetGravity())
				{
					TurnGravityOn(true);
					cout << "Gravity is on" << endl;
				}
				else
				{
					TurnGravityOn(false);
					cout << "Gravity is off" << endl;
				}
				break;
			case SDLK_f: // on close button pressed
				if (!GetFreeCam())
				{
					SerFreeCam(true);
					cout << "Free camera is on" << endl;
				}
				else
				{
					SerFreeCam(false);
					cout << "Free camera is off" << endl;
				}
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
	cout << "\t\t\tHelp Menu" << endl;
	cout << "1. WASD to Move" << endl;
	cout << "2. QE to go up and down" << endl;
	cout << "3. Hold RMB to look around" << endl;
	cout << "4. Mouse Scroll Up increase FOV" << endl;
	cout << "5. Mouse Scroll Down decrease FOV" << endl;
	cout << "6. R to reset FOV" << endl;
	cout << "7. LShift to go faster" << endl;
	cout << "8. LCtrl to go slow walk/speed" << endl;
	cout << "9. G to activate gravity" << endl;
	cout << "10. F to activate free camera" << endl << endl;
}

bool Input::IsMouseButtonDown(MouseButtons Button)
{
	return MouseButtonStates[Button];
}

void Input::ShowCursor(bool bVisibility)
{
	static SDL_bool bIsVisible = SDL_FALSE;

	//only run if the visibility of the cursor is opposite to what the input is asking for
	//i.e if we turn off the cursor but it's already off we dont need to turn it off
	//if the cursor is off and we ask for it to be on
	if (bVisibility && bIsVisible == SDL_TRUE)
	{
		bIsVisible = SDL_FALSE;
		SDL_SetRelativeMouseMode(bIsVisible);
	}
	//if the cursor is on and we ask for it to be off
	else if (!bVisibility && bIsVisible == SDL_FALSE) {
		bIsVisible = SDL_TRUE;
		SDL_SetRelativeMouseMode(bIsVisible);
	}
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
