#pragma once

#include "Position.h"
class Player {
	Pos pos;
	char** p;
	char** DP;	//delete player;
	int width = 5, height = 3;
	int x, y;	//position
	bool isDead;
public:
	Player();
	Player(Pos pos);
	char** getPlayer();
	char** getDeletePlayer();
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	Pos getPos();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void createDeletePlayer();
	bool Collision(Pos pos, int w, int h);
	void DeadPlayer();
	bool checkDead();
	~Player();
};
