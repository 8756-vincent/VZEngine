#include "VZEngine/Game.h"
int main(int argc, char** argv) {

	Game::GetGameInstance().Start("VZEngine", false, 720, 720);

	Game::DestroyGameInstance();

	return 0;
}