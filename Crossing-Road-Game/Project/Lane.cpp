#include "Lane.h"
Lane::Lane(bool direction, int speed, bool redLight, int curRow)
{
	this->direction = direction;
	this->speed = speed;
	this->redLight = redLight;
	this->curRow = curRow;
	enemy.reserve(100);
}

bool Lane::pushEnemy(Enemy* newEnemy)
{
	if (!direction) {
		newEnemy->updatePosition(0, RIGHTMAP - newEnemy->getY());
	}
	if (newEnemy->getY() > RIGHTMAP || newEnemy->getY() <= 3 || (enemy.size() && abs(enemy.back()->getY() - newEnemy->getY()) <= 8)) {
		return false;
	}
	enemy.push_back(newEnemy);
	printNewEnemy(newEnemy->getPos(), newEnemy->shape(), newEnemy->getWidth(), newEnemy->getHeight());
	return true;
}

int Lane::StepNewState(int t)
{
	int nDelete = 0;
	if ((redLight && (rand() % 8 == 0)) || (!redLight && (rand() % 15 == 0)) || (t == 0)) {
		reverseRedLight();

	}
	if (redLight) {
		txtColor(12);
	}
	else {
		txtColor(10);
	}
	if (direction)
	{
		gotoXY(RIGHTMAP + 63, curRow + 1);
	}
	else
	{
		gotoXY(LEFTMAP - 1, curRow + 1);
	}
	if (curRow != 1)
		cout << (char)254;
	txtColor(7);
	if (((t % speed) != 0) && t != 0)
		return nDelete; 
	if (redLight)
		return nDelete;
	vector <Enemy*> newEnemy;
	newEnemy.reserve(100);
	for (int i = 0; i < (int)enemy.size(); ++i) {
		Enemy* curEnemy = enemy[i];
		int dy = -1;
		if (direction)
			dy = 1;
		deleteOldEnemy(curEnemy->getPos(), curEnemy->getWidth(), curEnemy->getHeight());
		curEnemy->updatePosition(0, dy);

		bool canPrint = printNewEnemy(curEnemy->getPos(), curEnemy->shape(), curEnemy->getWidth(), curEnemy->getHeight());
		if (!canPrint) {
			curEnemy->goOutMap();
			++nDelete;
		}
		if (curEnemy->isOutOfMap()) {
			delete curEnemy;
		}
		else {
			newEnemy.push_back(curEnemy);
		}
	}
	enemy = newEnemy;
	return nDelete;
}

void Lane::deleteOldEnemy(Pos pos, int w, int h)
{
	int X = pos.getX();
	int Y = pos.getY();
	if (Y == LEFTMAP) 
		return;
	if (Y > RIGHTMAP) 
		return;
	for (int i = 0; i < h; ++i) {
		for (int j = max(1, Y); j <= min(RIGHTMAP, Y + w - 1); ++j) {
			gotoXY(Y + j, X + i);
			cout << ' ';
		}
	}
}

bool Lane::printNewEnemy(Pos pos, char** shape, int w, int h)
{
	txtColor(0);
	int X = pos.getX();
	int Y = pos.getY();
	if (Y == LEFTMAP) 
		return 0;
	if (Y > RIGHTMAP) 
		return 0;
	for (int i = 0; i < h; ++i) {
		for (int j = max(1, Y); j <= min(RIGHTMAP, Y + w - 1); ++j) {
			gotoXY(Y + j, X + i);
			cout << shape[i][j - max(1, Y)];
		}
	}
	return 1;
}

vector<Enemy*> Lane::getEnemy()
{
	return enemy;
}
void Lane::reverseRedLight()
{
	redLight = !redLight;
}
int Lane::getCurRow()
{
	return curRow;
}
int Lane::getDirection()
{
	return direction;
}
int Lane::getSpeed()
{
	return speed;
}
int Lane::getRedLight()
{
	return redLight;
}