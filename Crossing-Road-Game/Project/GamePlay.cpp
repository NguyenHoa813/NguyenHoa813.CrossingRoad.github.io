#include "GamePlay.h"


void GamePlay::drawMenu()
{

	while (true)
	{
		if (constVar::isMute == false)
			PlaySound(TEXT("Sound\\start.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		txtColor(15);
		/*clrscr();*/ system("cls");
		logoCrossingRoad();
		int x = 60, y = 19;
		txtColor(0);
		for (int i = 0; i < 19; i++)
		{
			gotoXY(x + i, y);
			cout << Border_Up;
			gotoXY(x + i, y + 8);
			cout << Border_Down;
		}
		for (int i = 0; i < 9; i++)
		{
			gotoXY(x - 1, y + i);
			cout << Border_Vertical;
			gotoXY(x + 19, y + i);
			cout << Border_Vertical;
		}
		gotoXY(x + 5, y + 1);
		cout << "NEW GAME";
		gotoXY(x + 5, y + 3);
		cout << "LOAD GAME";
		gotoXY(x + 5, y + 5);
		cout << "SETTINGS";
		gotoXY(x + 7, y + 7);
		cout << "QUIT";

		Nocursortype();
		int cpt = 0;
		while (true)
		{
			char choice = _getch();
			txtColor(0);
			gotoXY(x + 4, y + 1);
			cout << " NEW GAME ";
			gotoXY(x + 4, y + 3);
			cout << " LOAD GAME ";
			gotoXY(x + 4, y + 5);
			cout << " SETTINGS ";
			gotoXY(x + 6, y + 7);
			cout << " QUIT ";
			if (choice == KEY_DOWN || choice == 'S' || choice == 's')
			{
				cpt++;
				if (cpt > 4)
					cpt = 1;
			}
			if (choice == KEY_UP || choice == 'W' || choice == 'w')
			{
				cpt--;
				if (cpt < 1)
					cpt = 4;
			}
			if (cpt == 1)
			{
				txtColor(155);
				gotoXY(x + 4, y + 1);
				cout << " NEW GAME ";
				if (choice == KEY_ENTER)
				{
					loadingBar();
					newGame();
					break;
				}
			}
			if (cpt == 2)
			{
				txtColor(155);
				gotoXY(x + 4, y + 3);
				cout << " LOAD GAME ";
				if (choice == KEY_ENTER)
				{
					Sleep(500);
					if (LoadGame())
					{
						newGame();
						break;
					}
					else
					{
						break;
					}
				}

			}
			if (cpt == 3)
			{
				txtColor(155);
				gotoXY(x + 4, y + 5);
				cout << " SETTINGS ";
				if (choice == KEY_ENTER)
				{
					SettingsGame();
					break;
				}
			}
			if (cpt == 4)
			{
				txtColor(155);
				gotoXY(x + 6, y + 7);
				cout << " QUIT ";
				if (choice == KEY_ENTER)
				{
					txtColor(15);
					system("cls");
					txtColor(0);
					return;
				}
			}
		}
		cout << "\n\n\n";
	}
}

bool GamePlay::newGame()
{
	char key;
	if (!isLoad)
	{
		map.~Map();
		new(&map) Map();
	}
	txtColor(15);
	system("cls");
	map.drawMap();
	isPause = false;
	if (!isLoad)
		map.initializeNewState();
	isLoad = false;
	while (!map.isEnd())
	{
		map.randomNewState();
		if (isPause == true)
		{
			gotoXY(126, 20); txtColor(12); cout << Square_Piece;
			cout << " PAUSE GAME";
			txtColor(0);
			gotoXY(128, 22);
			cout << " RESUME";
			gotoXY(128, 24);
			cout << " QUIT";

			int temp = 0;
			while (true)
			{
				char lc = _getch();
				txtColor(0);
				gotoXY(128, 22);
				cout << " RESUME ";
				gotoXY(128, 24);
				cout << " QUIT ";
				if (lc == 'S' || lc == 's')
				{
					temp = temp + 1;
					if (temp > 2)
						temp = 1;
				}
				if (lc == 'W' || lc == 'w')
				{
					temp = temp - 1;
					if (temp < 1)
						temp = 2;
				}
				if (temp == 1)
				{
					txtColor(155);
					gotoXY(128, 22);
					cout << " RESUME ";
					if (lc == KEY_ENTER)
					{
						isPause = false;
						txtColor(15);
						gotoXY(126, 20);
						cout << " PAUSE GAME  ";
						gotoXY(128, 22);
						cout << " RESUME ";
						gotoXY(128, 24);
						cout << " QUIT ";
						txtColor(0);
						break;
					}
				}
				if (temp == 2)
				{
					txtColor(155);
					gotoXY(128, 24);
					cout << " QUIT ";
					if (lc == KEY_ENTER)
					{
						isPause = false;
						Sleep(200);
						return true;
					}
				}
			}
		}
		if (_kbhit())
		{
			char key = _getch();
			if (key == 'W' || key == 'w')
				map.UpdatePositionPlayer('w');
			if (key == 'S' || key == 's')
				map.UpdatePositionPlayer('s');
			if (key == 'a' || key == 'A')
				map.UpdatePositionPlayer('a');
			if (key == 'd' || key == 'D')
				map.UpdatePositionPlayer('d');


			if (key == 'p' || key == 'P')
				isPause = true;
			if (key == 'k' || key == 'K')
			{
				SaveGame();
			}
			if (key == 'l' || key == 'L')
			{
				if (LoadGame())
				{
					newGame();
				}
				else
				{
					map.drawMap();
				}
			}
			map.drawPlayer();
		}
		if (map.isWin())
		{
			if (constVar::isMute == false && map.getLevel() != 3)
				PlaySound(TEXT("Sound\\CompleteStage.wav"), NULL, SND_ASYNC);
			if (map.printLevelUp())
			{
				txtColor(15);
				/*clrscr();*/ system("cls");
				map.nextLevel();
				map.drawMap();
				map.deletePlayer();
				map.initializeNewState();
				map.drawPlayer();
				
				if (constVar::isMute == false)
					PlaySound(TEXT("Sound\\start.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else
				return true;
		}
		
	}
	return false;
}

void GamePlay::SaveGame()
{
	txtColor(15);
	/*clrscr();*/ system("cls");
	logoSaveGame();
	string filename;
	map.deletePlayer();
	txtColor(11);
	gotoXY(15, 20);
	cout << "<Press ESC to escape>";
	txtColor(11);
	gotoXY(15, 15);
	cout << "Input file name to save: ";
	txtColor(0);
	char key;
	while ((key = _getch()) != 27) {
		switch (key) {
		case '\b':
			if (filename.size() != 0) {
				filename.pop_back();
				gotoXY(50, 15);
				cout << "                                                 ";
				gotoXY(50, 15);
				cout << filename;
			}
			break;
		case 13:
			map.saveGame(filename);
			break;
		default:
			filename.push_back(key);
			gotoXY(50, 15);
			cout << filename;
		}
		if (key == 13) break;
	}
	txtColor(15);
	/*clrscr();*/ system("cls");
	map.drawMap();
}
vector<string> GamePlay::getAllFileName(const string& name)
{
	vector<string> v;
	string path(name);
	path.append("\\*");
	std::wstring st = std::wstring(path.begin(), path.end());
	LPCWSTR sw = st.c_str();
	WIN32_FIND_DATA data;
	HANDLE hFind = FindFirstFile(sw, &data);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			wchar_t* txt = data.cFileName;
			wstring ws(txt);
			string str(ws.begin(), ws.end());
			if (str[0] == '.') continue;
			v.push_back(str);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
	return v;
}

bool GamePlay::LoadGame()
{
	string filename;
	txtColor(15);
	/*clrscr();*/ system("cls");
	vector<string> files = getAllFileName("LoadGame");
	if (files.size() == 0)
	{
		gotoXY(30, 15);
		cout << "No saved file to load!!!";
		Sleep(1000);
		return false;
	}
	int curPos = 0;
	txtColor(15);
	/*clrscr();*/ system("cls");
	txtColor(6);
	gotoXY(15, 5); cout << "**      *******      ****     *******" << endl;
	gotoXY(15, 6); cout << "**     **     **    **  **    **     *" << endl;
	gotoXY(15, 7); cout << "**     **     **   ********   **      * **     ** ******** **    ** **    **" << endl;
	gotoXY(15, 8); cout << "****** **     **  **********  **     *  ** * * ** **       ** *  ** **    **" << endl;
	gotoXY(15, 9); cout << "******  *******  **        ** *******   **  *  ** *******  **  * ** **    **" << endl;
	gotoXY(15, 10); cout << "                                        **     ** **       **   *** **    **" << endl;
	gotoXY(15, 11); cout << "                                        **     ** ******** **    ** ********" << endl;
	
	int x = 15, y = 4;
	txtColor(0);
	gotoXY(x - 8, y - 2);
	for (int i = 0; i < 91; ++i)
		cout << Border_Down;
	gotoXY(x - 5, y - 1);
	for (int i = 0; i < 86; ++i)
		cout << HORIZONTAL_PALE_PIECE;
	gotoXY(x - 5, y + 8);
	for (int i = 0; i < 86; ++i)
		cout << HORIZONTAL_PALE_PIECE;
	gotoXY(x - 8, 13);
	for (int i = 0; i < 91; ++i)
		cout << Border_Up;

	gotoXY(x - 6, y - 1);
	cout << UP_LEFT_CORNER_PALE_PIECE;
	gotoXY(x - 6, y + 8);
	cout << DOWN_LEFT_CORNER_PALE_PIECE;

	gotoXY(x + 80, y - 1);
	cout << UP_RIGHT_CORNER_PALE_PIECE;
	gotoXY(x + 80, y + 8);
	cout << DOWN_RIGHT_CORNER_PALE_PIECE;

	for (int i = 4; i < 12; ++i) {
		gotoXY(x - 6, i);
		cout << VERTICAL_PALE_PIECE;
	}
	for (int i = 4; i < 12; ++i) {
		gotoXY(x + 80, i);
		cout << VERTICAL_PALE_PIECE;
	}
	for (int i = 3; i < 13; ++i) {
		gotoXY(x - 8, i);
		cout << Border_Vertical;
	}
	for (int i = 3; i < 13; ++i) {
		gotoXY(x + 82, i);
		cout << Border_Vertical;
	}
	
	txtColor(11);
	gotoXY(30, 16); cout << "<Press ESC to escape...>";
	txtColor(0);
	gotoXY(30, 18);
	cout << "Choose Filename to load: ";

	for (int i = 0; i < (int)files.size(); ++i) {
		if (i == curPos) {
			gotoXY(26, 19 + i);
			cout << ">> ";
		}
		gotoXY(30, 19 + i);
		cout << files[i] << endl;
	}
	while (true) {
		if (_kbhit())
		{
			char key = _getch();
			if (key == 'w')
			{
				gotoXY(26, 19 + curPos);
				cout << "    " << files[curPos];
				curPos--;
				curPos = (curPos + files.size()) % files.size();
				gotoXY(26, 19 + curPos);
				cout << ">>  " << files[curPos];
			}
			if (key == 's')
			{
				gotoXY(26, 19 + curPos);
				cout << "    " << files[curPos];
				curPos++;
				curPos = (curPos + files.size()) % files.size();
				gotoXY(26, 19 + curPos);
				cout << ">>  " << files[curPos];
			}
			if (key == 13)
			{
				isLoad = true;
				map.loadGame(files[curPos]);
				txtColor(15);
				/*clrscr();*/ system("cls");
				//map.redrawMap();
				return true;
			}
			if (key == 27)
			{
				txtColor(15);
				/*clrscr();*/ system("cls");
				//map.redrawMap();
				return false;
			}
		}
		if (constVar::isMute == false)
			PlaySound(TEXT("Sound\\start.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Sleep(50);
	}
}
void GamePlay::logoSaveGame() {
	txtColor(15);
	/*clrscr();*/ system("cls");
	int x = 50;
	int y = 4;

	txtColor(0);
	gotoXY(x - 2, y);		cout << " _______  _______  __   __  _______    _______  _______  __   __  _______ " << endl;
	gotoXY(x - 2, y + 1);	cout << "|       ||   _   ||  | |  ||       |  |       ||   _   ||  |_|  ||       |" << endl;
	gotoXY(x - 2, y + 2);	cout << "|  _____||  |_|  ||  |_|  ||    ___|  |    ___||  |_|  ||       ||    ___|" << endl;
	gotoXY(x - 2, y + 3);	cout << "| |_____ |       ||       ||   |___   |   | __ |       ||       ||   |___ " << endl;
	gotoXY(x - 2, y + 4);	cout << "|_____  ||       ||       ||    ___|  |   ||  ||       ||       ||    ___|" << endl;
	gotoXY(x - 2, y + 5);	cout << " _____| ||   _   | |     | |   |___   |   |_| ||   _   || ||_|| ||   |___ " << endl;
	gotoXY(x - 2, y + 6);	cout << "|_______||__| |__|  |___|  |_______|  |_______||__| |__||_|   |_||_______|" << endl;

	txtColor(11);
	gotoXY(x - 8, y - 2);
	for (int i = 0; i < 86; ++i)
		cout << Border_Down;
	gotoXY(x - 5, y - 1);
	for (int i = 0; i < 81; ++i)
		cout << HORIZONTAL_PALE_PIECE;
	gotoXY(x - 5, y + 8);
	for (int i = 0; i < 81; ++i)
		cout << HORIZONTAL_PALE_PIECE;
	gotoXY(x - 8, 13);
	for (int i = 0; i < 86; ++i)
		cout << Border_Up;

	gotoXY(x - 6, y - 1);
	cout << UP_LEFT_CORNER_PALE_PIECE;
	gotoXY(x - 6, y + 8);
	cout << DOWN_LEFT_CORNER_PALE_PIECE;

	gotoXY(x + 75, y - 1);
	cout << UP_RIGHT_CORNER_PALE_PIECE;
	gotoXY(x + 75, y + 8);
	cout << DOWN_RIGHT_CORNER_PALE_PIECE;

	for (int i = 4; i < 12; ++i) {
		gotoXY(x - 6, i);
		cout << VERTICAL_PALE_PIECE;
	}
	for (int i = 4; i < 12; ++i) {
		gotoXY(x + 75, i);
		cout << VERTICAL_PALE_PIECE;
	}
	for (int i = 3; i < 13; ++i) {
		gotoXY(x - 8, i);
		cout << Border_Vertical;
	}
	for (int i = 3; i < 13; ++i) {
		gotoXY(x + 77, i);
		cout << Border_Vertical;
	}
}
void GamePlay::logoCrossingRoad() {
	txtColor(6);
	int x = 20;
	int y = 4;
	
	gotoXY(x - 1, y);		cout << " _______  ______    _______  _______  _______  __  ____     __  _______       ______    _______  _______  ______  " << endl;
	gotoXY(x - 1, y + 1);	cout << "|       ||    _ |  |       ||       ||       ||  ||    \\   |  ||  _____\\     |    _ |  |       ||   _   ||      | " << endl;
	gotoXY(x - 1, y + 2);	cout << "|       ||   | ||  |   _   ||  _____||  _____||  ||  |\\ \\  |  || |   ___     |   | ||  |   _   ||  |_|  ||  _    |" << endl;
	gotoXY(x - 1, y + 3);	cout << "|       ||   |_||_ |  | |  || |_____ | |_____ |  ||  | \\ \\ |  || |  |_  |    |   |_||_ |  | |  ||       || | |   |" << endl;
	gotoXY(x - 1, y + 4);	cout << "|      _||    __  ||  |_|  ||_____  ||_____  ||  ||  |  \\ \\|  || |    | |    |    __  ||  |_|  ||       || |_|   |" << endl;
	gotoXY(x - 1, y + 5);	cout << "|     |_ |   |  | ||       | _____| | _____| ||  ||  |   \\    || |____| |    |   |  | ||       ||   _   ||       |" << endl;
	gotoXY(x - 1, y + 6);	cout << "|_______||___|  |_||_______||_______||_______||__||__|    \\___||________|    |___|  |_||_______||__| |__||______| " << endl;

	txtColor(0);
	gotoXY(x - 8, y - 2);
	for (int i = 0; i < 130; ++i)
		cout << Border_Down;
	gotoXY(x - 5, y - 1);
	for (int i = 0; i < 125; ++i)
		cout << HORIZONTAL_PALE_PIECE;
	gotoXY(x - 5, y + 8);
	for (int i = 0; i < 125; ++i)
		cout << HORIZONTAL_PALE_PIECE;
	gotoXY(x - 8, 13);
	for (int i = 0; i < 130; ++i)
		cout << Border_Up;

	gotoXY(x - 6, y - 1);
	cout << UP_LEFT_CORNER_PALE_PIECE;
	gotoXY(x - 6, y + 8);
	cout << DOWN_LEFT_CORNER_PALE_PIECE;

	gotoXY(x + 119, y - 1);
	cout << UP_RIGHT_CORNER_PALE_PIECE;
	gotoXY(x + 119, y + 8);
	cout << DOWN_RIGHT_CORNER_PALE_PIECE;

	for (int i = 4; i < 12; ++i) {
		gotoXY(x - 6, i);
		cout << VERTICAL_PALE_PIECE;
	}
	for (int i = 4; i < 12; ++i) {
		gotoXY(x + 119, i);
		cout << VERTICAL_PALE_PIECE;
	}
	for (int i = 3; i < 13; ++i) {
		gotoXY(x - 8, i);
		cout << Border_Vertical;
	}
	for (int i = 3; i < 13; ++i) {
		gotoXY(x + 121, i);
		cout << Border_Vertical;
	}
	txtColor(0);
}
void GamePlay::loadingBar() {

	int x = 51;
	int y = 18;
	txtColor(15);
	/*clrscr();*/ system("cls");
	txtColor(0);
	logoCrossingRoad();

	y = 20;
	gotoXY(80, y - 1);	cout << "LOADING...";
	gotoXY(x - 1, y);
	for (int i = 0; i < 70; ++i)
		cout << Border_Down;

	gotoXY(x - 1, y + 2);
	for (int i = 0; i < 70; ++i)
		cout << Border_Up;

	gotoXY(x - 1, y + 1);
	cout << Border_Vertical;
	gotoXY(x + 68, y + 1);
	cout << Border_Vertical;

	gotoXY(x, y + 1);
	for (int i = 0; i < 68; ++i) {
		Sleep(20);
		txtColor(6);
		cout << char(178);
	}

}

void GamePlay ::emptyMenu()
{
	txtColor(0);
	for (int i = 18; i < 30; ++i) {
		gotoXY(59, i);
		for (int j = 0; j < 25; ++j) {
			cout << " ";
		}
	}
}

void GamePlay::displayConsole()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1280, 720, TRUE);
	FixConsoleWindow();
}

void GamePlay::SettingsGame()
{
	txtColor(0);
	emptyMenu();
	int x = 59;
	int y = 19;
	gotoXY(x + 1, y);
	for (int i = 0; i < 20; ++i)
		cout << Border_Up;
	for (int i = y; i < y + 7; ++i)
	{
		gotoXY(x, i);
		cout << Border_Vertical;
	}
	for (int i = y; i < y + 7; ++i)
	{
		gotoXY(x + 21, i);
		cout << Border_Vertical;
	}
	gotoXY(x + 1, y + 6);
	for (int i = 0; i < 20; ++i)
		cout << Border_Down;

	txtColor(0);
	gotoXY(x + 6, y + 1); cout << "MODE:";
	if (constVar::isHard == false) {
		gotoXY(x + 12, y + 1); cout << "EASY";
	}
	else {
		gotoXY(x + 12, y + 1); cout << "HARD";
	}
	gotoXY(x + 6, y + 3); cout << "SOUND:";
	if (constVar::isMute == false) {
		gotoXY(x + 13, y + 3); cout << "ON";
	}
	else {
		gotoXY(x + 13, y + 3); cout << "OFF";
	}
	gotoXY(x + 9, y + 5); cout << "BACK";

	int cnt = 0;
	while (true)
	{
		char choice = _getch();
		txtColor(0);
		gotoXY(x + 6, y + 1); cout << "MODE:";
		gotoXY(x + 6, y + 3); cout << "SOUND:";
		gotoXY(x + 8, y + 5); cout << " BACK ";

		if (choice == KEY_DOWN || choice == 'S' || choice == 's') {
			cnt++;
			if (cnt > 3)
				cnt = 1;
		}
		if (choice == KEY_UP || choice == 'W' || choice == 'w') {
			cnt--;
			if (cnt < 1)
				cnt = 3;
		}
		if (cnt == 1) {
			txtColor(155);
			gotoXY(x + 6, y + 1); cout << "MODE:";
			if (choice == KEY_ENTER) {
				if (constVar::isHard == true)
					constVar::isHard = false;
				else
					constVar::isHard = true;

				if (constVar::isHard == false) {
					txtColor(0);
					gotoXY(x + 12, y + 1); cout << "EASY";
				}
				else {
					txtColor(0);
					gotoXY(x + 12, y + 1); cout << "HARD";
				}
			}
		}
		if (cnt == 2) {
			txtColor(155);
			gotoXY(x + 6, y + 3); cout << "SOUND:";
			if (choice == KEY_ENTER) {
				if (constVar::isMute == true)
					constVar::isMute = false;
				else
					constVar::isMute = true;

				if (constVar::isMute == false) {
					txtColor(0);
					gotoXY(x + 13, y + 3); cout << "ON ";
					PlaySound(TEXT("Sound\\start.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				}
				else {
					txtColor(0);
					gotoXY(x + 13, y + 3); cout << "OFF";
					PlaySound(NULL, NULL, SND_ASYNC);
				}
			}
		}
		if (cnt == 3) {
			txtColor(155);
			gotoXY(x + 8, y + 5); cout << " BACK ";
			if (choice == KEY_ENTER) {
				
				return;
			}
		}
	}
}
