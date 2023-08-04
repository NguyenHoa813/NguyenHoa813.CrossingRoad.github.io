#pragma once
#include <iostream>
#include "Enemy.h"
using namespace std;

class Car : public Enemy {
	char** s;
public:
	Car();
	Car(Pos pos);
	char** shape();
	void testShape(int px, int py);
	int getType();
	int getWidth()
	{
		return 13;
	}
	void sound();
	~Car();
};