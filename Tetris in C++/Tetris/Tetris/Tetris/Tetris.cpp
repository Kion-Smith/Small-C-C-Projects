// Tetris.cpp : Defines the entry point for the console application.
// based of a youtbe tutorial by OneLoneCoder can be found at https://www.youtube.com/watch?v=8OK8_tHeCIA&index=3&list=LL8pDyb4hQUBUbgOxTT9lhlA&t=691s
#include "stdafx.h"
#include <iostream>
#include <string>
#include <Windows.h>

int rotatePiece(int, int, int);

std::wstring piece[7];

int screenWidth = 80;			
int screenHeight = 30;			

int boardWidth = 12;
int boardHeight = 18;

unsigned char *board = nullptr;


int main()
{

	// I
	piece[0].append(L"..X.");
	piece[0].append(L"..X.");
	piece[0].append(L"..X.");
	piece[0].append(L"..X.");

	// Z
	piece[1].append(L"..X.");
	piece[1].append(L".XX.");
	piece[1].append(L".X..");
	piece[1].append(L"....");

	// S
	piece[2].append(L".X..");
	piece[2].append(L".XX.");
	piece[2].append(L"..X.");
	piece[2].append(L"....");


	// O
	piece[3].append(L"....");
	piece[3].append(L".XX.");
	piece[3].append(L".XX.");
	piece[3].append(L"....");

	// T
	piece[4].append(L"..X.");
	piece[4].append(L".XX.");
	piece[4].append(L"..X.");
	piece[4].append(L"....");

	//L
	piece[5].append(L"....");
	piece[5].append(L".XX.");
	piece[5].append(L"..X.");
	piece[5].append(L"..X.");

	//J
	piece[6].append(L"....");
	piece[6].append(L".XX.");
	piece[6].append(L".X..");
	piece[6].append(L".X..");

	board = new unsigned char[boardWidth*boardHeight];
	for (int x = 0; x < boardWidth; x++)
	{
		for (int y = 0; y < boardHeight; y++)
		{
			//ternary expresion of if stament
			board[y*boardWidth + x] = (x == 0 || x == boardWidth - 1 || y == boardHeight - 1) ? 9 : 0;
		}
	}

	wchar_t *screen = new wchar_t[screenWidth*screenHeight];
	for (int i = 0; i < screenWidth*screenHeight; i++)
	{ 
		screen[i] = L' '; 
	}

	HANDLE Console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(Console);
	DWORD dwBytesWritten = 0;

	bool isRunning = true;

	while (isRunning)
	{
		for (int x = 0; x < boardWidth; x++)
		{
			for (int y = 0; y < boardHeight; y++)
			{
				screen[(y + 2)*screenWidth + (x + 2)] = L" ABCDEFG=#"[board[y*boardWidth + x]];
			}
		}
		WriteConsoleOutputCharacter(Console, screen, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten);
	}

	return 0;

}

int rotatePiece(int px, int py, int r)
{
	switch (r % 4)
	{
		// 0,90,180,270 rotation states
	case 0:
		return py * 4 + px;
	case 1:
		return 12 + py - (px * 4);
	case 2:
		return 15 - (py * 4) - px;
	case 3:
		return 3 - py + (px * 4);
	}
	return 0;
}