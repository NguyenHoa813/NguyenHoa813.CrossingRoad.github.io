#pragma once
#include <iostream>
using namespace std;

class Pos {
private:
	int x, y;
public:
	int getX();
	int getY();
	Pos() {};
	Pos(const int x, const int y) {
		this->x = x;
		this->y = y;
	}
	void setPos(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	~Pos() {};
};