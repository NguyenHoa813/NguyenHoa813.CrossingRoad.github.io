#pragma once
#include "Bird.h"
#include "Bus.h"
#include "Car.h"
#include "Dog.h"
#include "Enemy.h"
#include "Position.h"
#include <algorithm>

class Level {
private:
	int level;
	int maxEnemy, nEnemy, minSpeed, maxSpeed;
	int nLane;
	const int maxLevel = 3;
	void initia();
public:
	Level();
	Level(int level, int nEnemy);
	int getLevel();
	bool nextLevel();

	int getMaxSpeed();
	int getMinSpeed();
	Enemy* RandomNewEnemy(Pos pos);
	Enemy* GetNewEnemy(Pos pos, int type);
	void decNEnemy(int d);
};