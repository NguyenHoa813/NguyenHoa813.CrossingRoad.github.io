#include "Player.h"
#include "Map.h"
Player::Player()
{
	isDead = false;
	pos.setPos(32, 28);
	p = new char* [3];
	DP = new char* [3];
	for (int i = 0; i < 3; i++)
	{
		p[i] = new char[5];
		DP[i] = new char[5];
		for (int j = 0; j < 5; j++)
			DP[i][j] = ' ';
	}
	// Row 1
	for (int i = 0; i < 5; i++)
	{
		if (i == 2)
			p[0][i] = 'O';
		else
			p[0][i] = ' ';
	}
	//Row 2
	p[1][0] = '/';
	p[1][1] = '(';
	p[1][2] = '_';
	p[1][3] = ')';
	p[1][4] = '\\';

	//Row 3
	for (int i = 0; i < 5; i++) {
		if (i == 1)
			p[2][i] = '/';
		else if (i == 3)
			p[2][i] = '\\';
		else
			p[2][i] = ' ';
	}
}
Player::Player(Pos pos) : isDead(false), pos(pos)
{
	p = new char* [3];
	for (int i = 0; i < 3; i++)
	{
		p[i] = new char[5];
	}
	// Row 1
	for (int i = 0; i < 5; i++)
	{
		if (i == 2)
			p[0][i] = 'O';
		else
			p[0][i] = ' ';
	}
	//Row 2
	p[1][0] = '/';
	p[1][1] = '(';
	p[1][2] = '_';
	p[1][3] = ')';
	p[1][4] = '\\';

	//Row 3
	for (int i = 0; i < 5; i++) {
		if (i == 1)
			p[2][i] = '/';
		else if (i == 3)
			p[2][i] = '\\';
		else
			p[2][i] = ' ';
	}
}
void Player::createDeletePlayer()
{
	DP = new char* [3];
	for (int i = 0; i < 3; i++)
	{
		DP[i] = new char[5];
	}
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
			DP[i][j] = ' ';
}
bool Player::Collision(Pos pos, int w, int h)
{
	if (w == 5) {		//Bus
		if (this->getX() == pos.getX()) {
			if (this->getY() <= pos.getY() && (pos.getY() - this->getY() <= 2)) // xử lý bên trái
			{
				return true;
			}
			if (this->getY() >= pos.getY() && getY() - pos.getY() <= 3)			// xử lý bên phải
				return true;
		}
	}
	if (w == 2) {		//Bird
		if (this->getX() == pos.getX()) {
			if (this->getY() <= pos.getY() && (pos.getY() - this->getY() <= 2))
			{
				return true;
			}
			if (this->getY() >= pos.getY() && getY() - pos.getY() <= 2)
				return true;
		}
	}
	if (w == 10) {		//Car
		if (this->getX() == pos.getX()) {
			if (this->getY() <= pos.getY() && (pos.getY() - this->getY() <= 2))
			{
				return true;
			}
			if (this->getY() >= pos.getY() && getY() - pos.getY() <= 6)
				return true;
		}
	}
	if (w == 6) {		//Dog
		if (this->getX() == pos.getX()) {
			if (this->getY() <= pos.getY() && (pos.getY() - this->getY() <= 2))
			{
				return true;
			}
			if (this->getY() >= pos.getY() && getY() - pos.getY() <= 4)
				return true;
		}
	}
	return false;
}
void Player::DeadPlayer()
{
	isDead = true;
}
bool Player::checkDead()
{
	return isDead;
}
int Player::getX()
{
	return pos.getX();
}
int Player::getY()
{
	return pos.getY();
}
int Player::getWidth()
{
	return width;
}
int Player::getHeight()
{
	return height;
}
Pos Player::getPos()
{
	return pos;
}
char** Player::getPlayer() {
	return p;
}
char** Player::getDeletePlayer() {
	return DP;
}
void Player::MoveUp()
{
	if (pos.getX() <= Up_Map)
		return;
	pos.setPos(pos.getX() - 3, pos.getY());
}
void Player::MoveDown()
{
	if (pos.getX() >= Down_Map)
		return;
	pos.setPos(pos.getX() + 3, pos.getY());
}
void Player::MoveLeft()
{
	if (pos.getY() <= Left_Map)
		return;
	pos.setPos(pos.getX(), pos.getY() - 2);
}
void Player::MoveRight()
{
	if (pos.getY() + 2 >= Right_Map)
		return;
	pos.setPos(pos.getX(), pos.getY() + 2);
}

Player::~Player()
{
	for (int i = 0; i < 3; i++)
	{
		delete[] p[i];
		delete[] DP[i];
	}
	delete[] p;
	delete[] DP;
}
