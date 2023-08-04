#pragma once
#include "Enemy.h"

class Bus : public Enemy {
	char** s;
public:
	Bus();
	Bus(Pos pos);
	char** shape();
	void testShape();
	int getType();
	int getWidth()
	{
		return 8;
	}
	void sound();
	~Bus();
};