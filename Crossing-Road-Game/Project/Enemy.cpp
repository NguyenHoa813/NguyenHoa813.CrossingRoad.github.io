#include "Enemy.h"


Enemy::Enemy()
{
	checkOut = false;
}
Enemy::Enemy(Pos p)
{
	this->p = p;
	checkOut = false;
}
Pos Enemy::getPos()
{
	return p;
}

int Enemy::getX()
{
	return p.getX();
}

int Enemy::getY()
{
	return p.getY();
}


void Enemy::updatePosition(int dx, int dy) {
	p.setPos(p.getX() + dx, p.getY() + dy);
}

bool Enemy::isOutOfMap()
{
	return checkOut;
}

void Enemy::goOutMap()
{
	checkOut = true;
}
