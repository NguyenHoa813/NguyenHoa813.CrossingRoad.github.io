#pragma once
#include "Lane.h"
#include <vector>
class Road {
	vector<Lane*> subLanes;
public:
	Road();
	~Road() = default;
	bool pushEnemy(int row, Enemy * enemy); 
	void pushRow(Lane*);
	vector <Enemy*> listEnemy(); 
	vector <Lane*> listRow();
	int StepNewState(int t);
};