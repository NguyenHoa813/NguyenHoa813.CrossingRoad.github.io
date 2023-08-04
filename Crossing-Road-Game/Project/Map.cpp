#include "Map.h"
#include "Console.h"

Map::Map() {
	this->player;
};
void Map::drawMap()
{
	txtColor(15);
	/*clrscr();*/ system("cls");
	txtColor(0);
	for (int i = 0; i < 115; i++)
	{
		gotoXY(i + 3, 1);
		cout << Border_Up;
		gotoXY(i + 3, 35);
		cout << Border_Down;
	}
	for (int i = 0; i < 35; i++)
	{
		gotoXY(2, i + 1);
		cout << Border_Vertical;
		gotoXY(118, i + 1);
		cout << Border_Vertical;
	}
	// draw board game
	for (int i = 0; i < 32; i++)
	{
		gotoXY(i + 123, 1);
		cout << Border_Up;
		gotoXY(i + 123, 16);
		cout << Border_Down;
	}
	for (int i = 0; i < 16; i++)
	{
		gotoXY(122, i + 1);
		cout << Border_Vertical;
	}


	gotoXY(125, 2); cout << "CROSSING ROAD GAME";
	gotoXY(125, 3); cout << "LV." << level.getLevel();
	gotoXY(125, 5); cout << "CONTROL GAME";
	gotoXY(125, 6); cout << "[ W ]: UP" << endl;
	gotoXY(125, 7); cout << "[ S ]: DOWN" << endl;
	gotoXY(125, 8); cout << "[ A ]: LEFT" << endl;
	gotoXY(125, 9); cout << "[ D ]: RIGHT" << endl;

	gotoXY(125, 11); cout << "COMMANDS KEYBOARD";
	gotoXY(125, 12); cout << "[ K ]: Save Game";
	gotoXY(125, 13); cout << "[ L ]: Load Game";
	gotoXY(125, 14); cout << "[ P ]: Pause Game";
	drawPlayer();
}
void Map::checkMap()
{
	gotoXY(60, 17);
	cout << Border_Up;
	gotoXY(5, 31);
	cout << Border_Vertical;
}
int Map::draw(Pos pos, char** shape, int w, int h) {
	txtColor(0);
	int X = pos.getX();
	int Y = pos.getY();
	if (Y + w <= 0) return 0;
	if (Y > width) return 0;
	for (int i = 0; i < h; ++i) {
		for (int j = max(1, Y); j <= min(width, Y + w - 1); ++j) {
			gotoXY(Y + j, X + i);
			cout << shape[i][j - max(1, Y)];
		}
	}
	return 1;
}
void Map::deletePlayer()
{
	player.createDeletePlayer();
	draw(player.getPos(), player.getDeletePlayer(), player.getWidth(), player.getHeight());
}
void Map::drawPlayer()
{
	draw(player.getPos(), player.getPlayer(), player.getWidth(), player.getHeight());
}

void Map::UpdatePositionPlayer(char c)
{
	deletePlayer();
	if (c == 'w')
		player.MoveUp();
	else if (c == 's')
		player.MoveDown();
	else if (c == 'a')
		player.MoveLeft();
	else if (c == 'd')
		player.MoveRight();
	else
		return;
}
void Map::initializeNewState() {
	player.~Player();
	new(&player) Player();
	roadData.~Road();
	new(&roadData) Road();
	int padding[10];
	for (int i = 0; i < 10; ++i) {
		padding[i] = 0;
		int speed = rand() % (level.getMinSpeed() - level.getMaxSpeed() + 1) + level.getMaxSpeed();
		bool direction = rand() % 2;
		bool redLight = rand() % 2;	
		roadData.pushRow(new Lane(direction, speed, redLight, (i * 3) + 1));
	}
	Enemy* newEnemy;
	Pos pos;
	int tryCount = 10000;
	while (tryCount--) {
		int rRow = (rand() % 9) + 1;
		padding[rRow] += (rand() % 20) + 9;
		pos = Pos((rRow * 3) + 2, padding[rRow]);
		newEnemy = level.RandomNewEnemy(pos);
		if (!newEnemy)
			break;
		if (!roadData.pushEnemy(rRow, newEnemy)) {
			level.decNEnemy(1);
			delete newEnemy;
		};
	}
	Sleep(200);
	roadData.StepNewState(0);
}
void Map::randomNewState() {
	srand(time(NULL));
	Enemy* newEnemy;
	Pos pos;
	int tryCount = 10000;
	while (tryCount--) {
		int rRow = (rand() % 9) + 1;
		pos = Pos((rRow * 3) + 2, 4);
		newEnemy = level.RandomNewEnemy(pos);
		if (!newEnemy)
			break;
		if (!roadData.pushEnemy(rRow, newEnemy)) {
			level.decNEnemy(1);
			delete newEnemy;
		};
	}
	++t;
	int tmp = roadData.StepNewState(t);
	level.decNEnemy(tmp);
	isDead();
}

void Map::isDead()
{
	vector<Enemy*> enemyList = roadData.listEnemy();
	for (int i = 0; i < enemyList.size(); i++)
	{
		if (player.Collision(enemyList[i]->getPos(), enemyList[i]->getWidth() - 3, enemyList[i]->getHeight()))
		{
			if (constVar::isMute == false)
			{
				enemyList[i]->sound();
			}
			player.DeadPlayer();
			deletePlayer();
			drawPlayer();
			Sleep(2000);
			txtColor(15);
			/*clrscr();*/ system("cls");
			deletePlayer();
			if (constVar::isMute == false)
				PlaySound(TEXT("Sound\\GameOver.wav"), NULL, SND_ASYNC);
			for (int i = 14; i >= 0; --i) {
				txtColor(15);
				/*clrscr();*/ system("cls");
				txtColor(i);
				printLoseGame();
				Sleep(220);
			}
			txtColor(0);
			char c;
			while (_kbhit())
				c=_getch();
			gotoXY(45, 27);		
			cout << "*** Press any key to continue ***";
			c=_getch();
			return;
		}
	}
}
void Map::saveGame(string file)
{
	ofstream fileout("./LoadGame/" + file + ".bin", ios::out | ios::binary);
	WriteFileBin(level.getLevel(), fileout);
	WriteFileBin(player.getX(), fileout);
	WriteFileBin(player.getY(), fileout);

	vector<Lane*> lane(roadData.listRow());
	for (int i = 0; i < 10; i++)
	{
		WriteFileBin(lane[i]->getCurRow(), fileout);
		WriteFileBin(lane[i]->getDirection(), fileout);
		WriteFileBin(lane[i]->getSpeed(), fileout);
		WriteFileBin(lane[i]->getRedLight(), fileout);
	
		vector<Enemy*> enemy(lane[i]->getEnemy());;
		WriteFileBin(enemy.size(), fileout);
		
		for (int j = 0; j < enemy.size(); j++)
		{
			WriteFileBin(enemy[j]->getX(), fileout);
			WriteFileBin(enemy[j]->getY(), fileout);
			WriteFileBin(enemy[j]->getType(), fileout);
		}
	}
	fileout.close();
}
bool Map::loadGame(string file)
{
	ifstream filein("./LoadGame/" + file, ios::in | ios::binary);
	if (!filein.is_open())
		return false;
	int lv = ReadFileBin(filein);
	level.~Level();
	new(&level) Level(lv, 0);
	int pX, pY;
	pX = ReadFileBin(filein);
	pY = ReadFileBin(filein);
	player.~Player();
	new(&player) Player(Pos(pX, pY));

	int nEnemy = 0;

	roadData.~Road();
	new(&roadData) Road();

	for (int i = 0; i < 10; i++)
	{
		int direction, speed, redLight, curRow;
		curRow = ReadFileBin(filein);
		direction = ReadFileBin(filein);
		speed = ReadFileBin(filein);
		redLight = ReadFileBin(filein);

		roadData.pushRow(new Lane(direction, speed, redLight, curRow));

		int enemySize = ReadFileBin(filein);
		nEnemy += enemySize;

		for (int j = 0; j < enemySize; j++)
		{
			int eX, eY, eType;
			eX = ReadFileBin(filein);
			eY = ReadFileBin(filein);
			eType = ReadFileBin(filein);
			roadData.pushEnemy(i, level.GetNewEnemy(Pos(eX, eY), eType));
		}
	}
	filein.close();
	return true;
}
void Map::WriteFileBin(int p, ofstream& fileout)
{
	fileout.write((char*)&p, sizeof(int));
}
int Map::ReadFileBin(ifstream& filein)
{
	int p;
	filein.read((char*)&p, sizeof(int));
	return p;
}

bool Map::isWin()
{
	if (player.getX() == 2)
		return true;
	return false;
}

bool Map::isEnd()
{
	return player.checkDead();
}

void Map::nextLevel()
{
	level.nextLevel();
}
int Map::getLevel()
{
	return level.getLevel();
}
void Map::printLoseGame()
{
	int x = 35;
	int y = 11;
	int z = 2;

	gotoXY(x, z);		cout << " __   __  _______  __   __    ___      _______  _______  _______    __   __   __ " << endl;
	gotoXY(x, z + 1);	cout << "|  | |  ||       ||  | |  |  |   |    |       ||       ||       |  |  | |  | |  |" << endl;
	gotoXY(x, z + 2);	cout << "|  |_|  ||   _   ||  | |  |  |   |    |   _   ||  _____||_     _|  |  | |  | |  |" << endl;
	gotoXY(x, z + 3);	cout << "|       ||  | |  ||  |_|  |  |   |    |  | |  || |_____   |   |    |  | |  | |  |" << endl;
	gotoXY(x, z + 4);	cout << "|_     _||  |_|  ||       |  |   |___ |  |_|  ||_____  |  |   |    |__| |__| |__|" << endl;
	gotoXY(x, z + 5);	cout << "  |   |  |       ||       |  |       ||       | _____| |  |   |     __   __   __ " << endl;
	gotoXY(x, z + 6);	cout << "  |___|  |_______||_______|  |_______||_______||_______|  |___|    |__| |__| |__|" << endl;

	gotoXY(x-10, y);
	cout << R"(                                               ____                       )" << "\n";
	gotoXY(x-10, y + 1);
	cout << R"(                                           __,-~~/~    `---.                  )" << "\n";
	gotoXY(x-10, y + 2);
	cout << R"(                                         _/_,---(      ,    )                 )" << "\n";
	gotoXY(x-10, y + 3);
	cout << R"(                                     __ /        <    /   )  \___             )" << "\n";
	gotoXY(x-10, y + 4);
	cout << R"(                      - ------===;;;'====------------------===;;;===----- -  -)" << "\n";
	gotoXY(x-10, y + 5);
	cout << R"(                                      \/  ~"~"~"~"~"~\~"~)~" / )" << "\n";
	gotoXY(x-10, y + 6);
	cout << R"(                                        (_ (   \  (     >    \)               )" << "\n";
	gotoXY(x-10, y + 7);
	cout << R"(                                         \_( _ <         >_>'                 )" << "\n";
	gotoXY(x-10, y + 8);
	cout << R"(                                            ~ `-i' ::>|--"                    )" << "\n";
	gotoXY(x-10, y + 9);
	cout << R"(                                                I;|.|.|                       )" << "\n";
	gotoXY(x-10, y + 10);
	cout << R"(                                               <|i::|i|`.                     )" << "\n";
	gotoXY(x-10, y + 11);
	cout << R"(                                              (` ^'"`-' ")                    )";
	gotoXY(x - 10, y + 12);
	cout << R"(                   ------------------------------------------------------------- )";

}

bool Map::printLevelUp()
{
	if (level.getLevel() == 3)
	{
		printCongrats();
		return false;
	}
	else {
		txtColor(15);
		/*clrscr();*/ system("cls");
		drawMap();
		deletePlayer();
		gotoXY(15, 15); cout << "******    *******       *******      *******    *******    ******     *******      ###   ###" << endl;
		gotoXY(15, 16); cout << "**        **     **    **     **   **         **           **         **     *     ###   ###" << endl;
		gotoXY(15, 17); cout << "**        ** *  **    **       **    ****       ****       ******     **      *    ###   ###" << endl;
		gotoXY(15, 18); cout << "**        **   **      **     **         **         **     **         **     *     ###   ###" << endl;
		gotoXY(15, 19); cout << "******    **    **      *******    *****      *****        ******     *******     ::::: ::::: " << endl;
		gotoXY(35, 21); cout << "Continue ?" << endl;
		int pos = 0, x = 36, y = 22;
		int cpt = 0;
		txtColor(0);
		gotoXY(x, y);
		cout << " <YES> ";
		gotoXY(x, y + 1);
		cout << " <NO> ";
		while (1) {
			char choice = _getch();
			txtColor(0);
			gotoXY(x, y);
			cout << " <YES> ";
			gotoXY(x, y + 1);
			cout << " <NO> ";
			if (choice == 's' || choice == 'S')
			{
				cpt++;
				if (cpt > 2)
					cpt = 1;
			}
			if (choice == 'w' || choice == 'W')
			{
				cpt--;
				if (cpt < 1)
					cpt = 2;
			}
			if (cpt == 1)
			{
				txtColor(155);
				gotoXY(x, y);
				cout << " <YES> ";
				if (choice == KEY_ENTER)
					return true;
			}
			if (cpt == 2)
			{
				txtColor(155);
				gotoXY(x, y+1);
				cout << " <NO> ";
				if (choice == KEY_ENTER)
					return false;
			}
		}
	}
}

void Map::printCongrats()
{
	Sleep(500);
	txtColor(15);
	/*clrscr();*/ system("cls");
	drawMap();
	deletePlayer();
	if(constVar::isMute == false)
		PlaySound(TEXT("Sound\\Victory.wav"), NULL, SND_ASYNC);
	int x = 1;
	int y = 8;
	txtColor(6);
	gotoXY(x + 34, y + 6);   cout << " __   __  _______  __   __    _     _  ___   __    _    __   __   __ " << endl;
	gotoXY(x + 34, y + 7);	 cout << "|  | |  ||       ||  | |  |  | | _ | ||   | |  |  | |  |  | |  | |  |" << endl;
	gotoXY(x + 34, y + 8);	 cout << "|  |_|  ||   _   ||  | |  |  | || || ||   | |   |_| |  |  | |  | |  |" << endl;
	gotoXY(x + 34, y + 9);   cout << "|       ||  | |  ||  |_|  |  |       ||   | |       |  |  | |  | |  |" << endl;
	gotoXY(x + 34, y + 10);	 cout << "|_     _||  |_|  ||       |  |       ||   | |  _    |  |__| |__| |__|" << endl;
	gotoXY(x + 34, y + 11);	 cout << "  |   |  |       ||       |  |   _   ||   | | | |   |   __   __   __ " << endl;
	gotoXY(x + 34, y + 12);	 cout << "  |___|  |_______||_______|  |__| |__||___| |_|  |__|  |__| |__| |__|" << endl;
	txtColor(0);
	char c;
	Sleep(3000);
	while (_kbhit())
		c=_getch();
	gotoXY(45, y+15);		cout << "*** Press any key to continue ***";
	txtColor(0);
	c=_getch();
	return;
}
