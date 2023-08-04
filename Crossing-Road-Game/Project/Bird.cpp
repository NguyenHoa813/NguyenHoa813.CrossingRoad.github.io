#include "Bird.h"
#include "Map.h"
//>' )
//( ( \
// ''|\

Bird::Bird()
{
	s = new char* [3];
	for (int i = 0; i < 3; i++)
		s[i] = new char[5];
	s[0][0] = '>'; s[0][1] = '\''; s[0][2] = ' '; s[0][3] = ')'; s[0][4] = ' ';

	s[1][0] = s[1][2] = '('; s[1][1] = s[1][3] = ' '; s[1][4] = '\\';

	s[2][0] = ' '; s[2][1] = s[2][2] = '\''; s[2][3] = '|'; s[2][4] = '\\';
}

Bird::Bird(Pos pos) : Enemy(pos)
{
	s = new char* [3];
	for (int i = 0; i < 3; i++)
		s[i] = new char[5];
	s[0][0] = '>'; s[0][1] = '\''; s[0][2] = ' '; s[0][3] = ')'; s[0][4] = ' ';

	s[1][0] = s[1][2] = '('; s[1][1] = s[1][3] = ' '; s[1][4] = '\\';

	s[2][0] = ' '; s[2][1] = s[2][2] = '\''; s[2][3] = '|'; s[2][4] = '\\';

}

char** Bird::shape()
{
	return s;
}

void Bird::testShape()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			gotoXY(j, i);
			cout << s[i][j];
		}
	}
}

int Bird::getType()
{
	return 0;
}

void Bird::sound()
{
	PlaySound(TEXT("Sound\\Bird.wav"), NULL, SND_ASYNC);
}

Bird::~Bird()
{
	for (int i = 0; i < 3; i++)
		delete[] s[i];
	delete[] s;
}
