#pragma once
#include "Map.h"

class GamePlay {
	Map map;
	bool isLoad = false;
	bool isPause = false;
public:
	void drawMenu();
	bool newGame();
	void SaveGame();
	bool LoadGame();
	vector<string> getAllFileName(const string& name);
	void logoSaveGame();
	void logoCrossingRoad();
	void loadingBar();
	void SettingsGame();
	void emptyMenu();
	void displayConsole();
};