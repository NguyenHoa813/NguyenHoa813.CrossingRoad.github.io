#pragma once
#include "Enemy.h"
#include <vector>
#include "Console.h"
#define RIGHTMAP 56
#define LEFTMAP 2
class Lane {
private:
	vector<Enemy*> enemy;
	bool redLight = false;
	bool direction;
	int speed;
	int curRow;
public:
	Lane() = default;
	Lane(bool direction, int speed, bool redLight, int curRow);
	bool pushEnemy(Enemy* newEnemy);
	int StepNewState(int t);
	void deleteOldEnemy(Pos pos, int w, int h);
	bool printNewEnemy(Pos pos, char** shape, int w, int h);

	vector<Enemy*> getEnemy();
	void reverseRedLight();
	int getCurRow();
	int getDirection();
	int getSpeed();
	int getRedLight();
};