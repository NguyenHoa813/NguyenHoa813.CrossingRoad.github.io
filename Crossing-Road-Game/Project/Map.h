#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Player.h"
#include "Car.h"
#include "Bus.h"
#include "Enemy.h"
#include "Level.h"
#include "Road.h"
#include <fstream>
using namespace std;

#define Border_Vertical char(219);
#define Border_Down char(220);
#define Border_Up char(223);
#define Border_mid char(254);
#define Square_Piece char(254)

#define HORIZONTAL_PALE_PIECE char(205);
#define VERTICAL_PALE_PIECE char(186);
#define UP_LEFT_CORNER_PALE_PIECE char(201)
#define UP_RIGHT_CORNER_PALE_PIECE char(187)
#define DOWN_LEFT_CORNER_PALE_PIECE char(200)
#define DOWN_RIGHT_CORNER_PALE_PIECE char(188)

#define KEY_DOWN 80
#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_ENTER 13


#define Left_Map 3
#define Right_Map 58
#define Up_Map 3
#define Down_Map 32

class Map {
private:
	const int width = 113, height = 32;
	Player player;
	Road roadData;
	Level level;
	int t = 0;
	bool checkPause;
public:
	Map();
	~Map() = default;
	
	void drawMap();
	void checkMap();
	void deletePlayer();
	void drawPlayer();
	void UpdatePositionPlayer(char c);
	void initializeNewState();
	void randomNewState();
	int draw(Pos pos, char** shape, int w, int h);
	void isDead();
	void saveGame(string file);
	bool loadGame(string file);
	void WriteFileBin(int p, ofstream& fileout);
	int ReadFileBin(ifstream& filein);
	bool isWin();
	bool isEnd();
	void nextLevel();
	void printLoseGame();
	bool printLevelUp();
	void printCongrats();
	int getLevel();
};
