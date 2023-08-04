#include "Dog.h"
#include "Map.h"
 /* (___()'`;
    /,    /`
    \\"--\\*/
Dog::Dog()
{
	s = new char* [3];
	for (int i = 0; i < 3; i++)
	{
		s[i] = new char[9];
	}
	s[0][0] = s[0][4] = '('; s[0][1] = s[0][2] = s[0][3] = '_';
	s[0][5] = ')'; s[0][6] = '\''; s[0][7] = '`'; s[0][8] = ';';
	
	s[1][0] = s[1][6] = '/'; s[1][1] = ','; s[1][7] = '`';
	s[1][2] = s[1][3] = s[1][4] = s[1][5] = s[1][8] = ' ';

	s[2][0] = s[2][1] = s[2][5] = s[2][6] = '\\'; s[2][8] = ' ';
	s[2][3] = s[2][4] = '-'; s[2][2] = '"'; s[2][7] = ' ';
}

Dog::Dog(Pos pos) : Enemy(pos)
{
	s = new char* [3];
	for (int i = 0; i < 3; i++)
	{
		s[i] = new char[9];
	}
	s[0][0] = s[0][4] = '('; s[0][1] = s[0][2] = s[0][3] = '_';
	s[0][5] = ')'; s[0][6] = '\''; s[0][7] = '`'; s[0][8] = ';';

	s[1][0] = s[1][6] = '/'; s[1][1] = ','; s[1][7] = '`';
	s[1][2] = s[1][3] = s[1][4] = s[1][5] = s[1][8] = ' ';

	s[2][0] = s[2][1] = s[2][5] = s[2][6] = '\\'; s[2][8] = ' ';
	s[2][3] = s[2][4] = '-'; s[2][2] = '"'; s[2][7] = ' ';
}

char** Dog::shape()
{
	return s;
}

void Dog::testShape()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			gotoXY(j, i);
			cout << s[i][j];
		}
	}
}

int Dog::getType()
{
	return 3;
}

void Dog::sound()
{
	PlaySound(TEXT("Sound\\Dog.wav"), NULL, SND_ASYNC);
}

Dog::~Dog()
{
	for (int i = 0; i < 3; i++)
	{
		delete[] s[i];
	}
	delete[] s;
}
