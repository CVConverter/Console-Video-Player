#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <algorithm>

#include <fstream>
#include <thread>

#include <windows.h>

#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

#include <opencv2/opencv.hpp>

using namespace std;

#define cmd(str) system(((string)str).c_str())

bool stop = false;
int AStart = -2;

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
void fullScreen(HWND hwnd)
{
	ShowWindow(hwnd, SW_MAXIMIZE);
}
void setFontSize(int size = 6)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = size;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void playVideo(string target)
{
	if (target.length() < 5)
	{
		return;
	}

	cv::namedWindow("video", cv::WINDOW_KEEPRATIO);
	cv::VideoCapture cap;
	cap.open(target);
	register cv::Mat now;
	register double delay = 1000.0 / cap.get(cv::CAP_PROP_FPS);

	register clock_t start;
	register unsigned long long currentFrame = 0;

	++AStart;
	while (AStart) {};
	start = clock();
	while(!stop)
	{
		++currentFrame;
		cap >> now;
		if (now.empty())
		{
			break;
		}
		cv::imshow("video", now);
		while (1.0 * (clock() - start) / CLOCKS_PER_SEC * 1000 / delay < currentFrame)
		{
			cv::waitKey(1);
		}
	}
}

void play(string target, string tSound)
{
	noQuickEdit();
	showCursor(0);
	fullScreen(FindWindowA("ConsoleWindowClass", "Console Video Player"));
	setFontSize();

	fstream fin;
	fin.open(target);
	if (!fin.is_open())
	{
		cerr << "Failed to open target.\n";
		exit(1);
	}
	int fps;
	fin >> fps;
	register clock_t start, cur;
	register double delay = 1000.0 / fps;
	register unsigned long long currentFrame = 0;
	register char line[1024];
	memset(line, '\0', sizeof(line));

	if (tSound.size()>2)
	{
		PlaySoundA(tSound.c_str(), NULL, SND_FILENAME | SND_ASYNC);
	}

	++AStart;
	while (AStart) {};
	start = clock();
	while (!fin.eof())
	{
		++currentFrame;
		gotoxy(0, 0);
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
		while (1.0 * (clock() - start) / CLOCKS_PER_SEC * 1000 / delay < currentFrame)
		{
			Sleep(1);
		}
	}
}

int main(int argc, char *argv[])
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	system("title Console Video Player");

	string targ, tSnd, tVdo;
	if (argc > 1)
	{
		targ = argv[1];
		tSnd = argv[1];
		tVdo = argv[1];
		int i;
		char nametype[4] = "wav";
		char nametype2[4] = "mp4";
		for (i = 0; i < 3; ++i)
		{
			tSnd[targ.size() + i - 3] = nametype[i];
			tVdo[targ.size() + i - 3] = nametype2[i];
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
		fin.open(tVdo);
		if (fin.is_open())
		{
			fin.close();
		}
		else
		{
			fin.close();
			tVdo.clear();
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

	thread thdPlayVideo(playVideo, tVdo);
	play(targ, tSnd);
	stop = true;
	if (thdPlayVideo.joinable())
	{
		thdPlayVideo.join();
	}
	return 0;
}
