#pragma once
#include <iostream>
#include <string>
#include <algorithm>

#include <fstream>
#include <windows.h>

#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

using namespace std;

#define cmd(str) system(((string)str).c_str())

void showCursor(bool state)
{
	// get buffer handle
	HANDLE hOutput;
	COORD coord = { 0, 0 };
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	// set visibility of the cursor
	CONSOLE_CURSOR_INFO cci = { 1,state };
	SetConsoleCursorInfo(hOutput, &cci);
}

inline void gotoxy(int x, int y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)x, (short)y });
}

void noQuickEdit()
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	mode &= ~ENABLE_INSERT_MODE;
	mode |= ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, mode);
	return;
}

void play(string target, string tSound)
{
	noQuickEdit();
	showCursor(0);

	fstream fin;
	fin.open(target);
	if (!fin.is_open())
	{
		cerr << "Failed to open target.\n";
		exit(1);
	}
	int fps;
	fin >> fps;
	register double currentFPS = 0, dur = 0;
	clock_t totalStart=clock(), totalEnd;
	register clock_t start, end;
	register char line[1024];
	register float averageSleep = 1000.0 / fps;
	register int currentFrame = 0;
	memset(line, '\0', sizeof(line));

	if (tSound.size()>2)
	{
		PlaySoundA(tSound.c_str(), NULL, SND_FILENAME | SND_ASYNC);
	}

	while (!fin.eof())
	{
		start = clock();
		gotoxy(0, 0);
		++currentFrame;
		while (!fin.eof())
		{
			fin.getline(line, 1024);
			if (!strncmp(line, "[ENDFRAME]", 10))
			{
				break;
			}
			fputs(line, stdout);
			cout << "\n";
		}
		while (clock() - start < averageSleep);
		end = clock();
		dur = end - start;
		currentFPS = 1000.0 / dur;
		if (currentFPS > fps)
		{
			averageSleep += 1;
		}
		else
		{
			averageSleep -= 1;
		}
	}
	totalEnd = clock();
	// std::cout << "\n\ntotal time:" << (totalEnd - totalStart) / CLOCKS_PER_SEC << endl;
}

int main(int argc, char *argv[])
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	system("title Console Video Player");

	string targ, tSnd;
	if (argc > 1)
	{
		targ = argv[1];
		tSnd = argv[1];
		int i;
		char nametype[4] = "wav";
		for (i = 0; i < 3; ++i)
		{
			tSnd[targ.size() + i - 3] = nametype[i];
		}

		ifstream fin;
		fin.open(tSnd);
		if (fin.is_open())
		{
			fin.close();
		}
		else
		{
			fin.close();
			tSnd.clear();
		}
	}
	else
	{
		std::cout << "Enter the target path: ";
		cin >> targ;
		std::cout << "Enter the target sound(optional, enter any single char to skip): ";
		cin >> tSnd;
	}

	system("cls");

	play(targ, tSnd);
	return 0;
}
