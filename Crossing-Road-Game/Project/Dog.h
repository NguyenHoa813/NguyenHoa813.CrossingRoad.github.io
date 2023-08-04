#pragma once
#include "Enemy.h"

class Dog : public Enemy {
	char** s;
public:
	Dog();
	Dog(Pos pos);
	char** shape();
	void testShape();
	int getType();
	int getWidth()
	{
		return 9;
	}
	void sound();
	~Dog();
};