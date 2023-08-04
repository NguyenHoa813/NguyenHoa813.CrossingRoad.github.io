#pragma once
#include "Enemy.h"

class Bird : public Enemy {
	char** s;
public:
	Bird();
	Bird(Pos pos);
	char** shape();
	void testShape();
	int getType();
	int getWidth()
	{
		return 5;
	}
	void sound();
	~Bird();
};