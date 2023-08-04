#include "Level.h"

void Level::initia()
{
	int difficulty = 50, maxE = 20;
	if (constVar::isHard)
	{
		difficulty = 10;
		maxE = 40;
	}
	nLane = 10;
	maxEnemy = min(maxE, nLane * 10);
	maxSpeed = difficulty - level * 2;  //speed nho ,toc do thuc nhanh
	minSpeed = difficulty - level * 1;
}

Level::Level()
{
	level = 1;
	nEnemy = 0;
	initia();
}

Level::Level(int level, int nEnemy)
{
	this->level = level;
	this->nEnemy = nEnemy;
	initia();
}

int Level::getLevel()
{
	return level;
}

bool Level::nextLevel()
{
	if (level == maxLevel)
		return false;
	level++;
	nEnemy = 0;
	return true;
}

int Level::getMaxSpeed()
{
	return maxSpeed;
}

int Level::getMinSpeed()
{
	return minSpeed;
}

Enemy* Level::RandomNewEnemy(Pos pos)
{
	if (nEnemy == maxEnemy)
		return NULL;
	if ((nEnemy < (maxEnemy / 2)) || rand() % 3)
	{
		++nEnemy;
		Enemy* pEnemy = NULL;
		int type = rand() % 4;
		switch (type)
		{
		case 0: {
			pEnemy = new Bird(pos);
			break;
		}
		case 1: {
			pEnemy = new Car(pos);
			break;
		}
		case 2: {
			pEnemy = new Bus(pos);
			break;
		}
		default:
			pEnemy = new Dog(pos);
			break;
		}
		return pEnemy;
	}
	return NULL;
}

Enemy* Level::GetNewEnemy(Pos pos, int type)
{
	++nEnemy;
	Enemy* pEnemy = NULL;
	switch (type)
	{
	case 0: {
		pEnemy = new Bird(pos);
		break;
	}
	case 1: {
		pEnemy = new Car(pos);
		break;
	}
	case 2: {
		pEnemy = new Bus(pos);
		break;
	}
	default:
		pEnemy = new Dog(pos);
		break;
	}
	return pEnemy;
}
void Level::decNEnemy(int d) {
	nEnemy -= d;
}