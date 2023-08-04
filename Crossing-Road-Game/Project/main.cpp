#include "GamePlay.h"
#include <filesystem>

bool constVar::isMute = false;
bool constVar::isHard = false;
int main() {
	GamePlay game;
	game.displayConsole();
	game.drawMenu();
	return 0;
}