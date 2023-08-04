#pragma once
#include <iostream>
#include "Position.h"
#include "Console.h"
using namespace std;
class Enemy {
private:
	Pos p;
	bool checkOut;
public:
	Pos getPos();
	int getX();
	int getY();
	Enemy();
	Enemy(Pos p);
	virtual ~Enemy() = default;
	virtual char** shape() = 0;
	virtual int getWidth()
	{
		return 8;
	}
	int getHeight()
	{
		return 3;
	}
	void updatePosition(int dx, int dy);
	bool isOutOfMap();
	void goOutMap();
	virtual int getType() = 0;
	virtual void sound() = 0;
};