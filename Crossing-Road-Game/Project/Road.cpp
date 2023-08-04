#include "Road.h"

Road::Road()
{
	subLanes.reserve(100);
}

bool Road::pushEnemy(int row, Enemy* enemy)
{
	if (row >= subLanes.size())
		return false;
	return subLanes[row]->pushEnemy(enemy);
}

void Road::pushRow(Lane* row)
{
	subLanes.push_back(row);
}

vector<Enemy*> Road::listEnemy()
{
	vector<Enemy*> listEnemy, temp;
	for (int i = 0; i < subLanes.size(); i++)
	{
		temp = subLanes[i]->getEnemy();
		listEnemy.insert(listEnemy.end(), temp.begin(), temp.end());
	}
	return listEnemy;
}

vector<Lane*> Road::listRow()
{
	return subLanes;
}

int Road::StepNewState(int t)
{
	int nDel = 0;
	for (int i = 0; i < subLanes.size(); i++)
	{
		nDel += subLanes[i]->StepNewState(t);
	}
	return nDel;
}
