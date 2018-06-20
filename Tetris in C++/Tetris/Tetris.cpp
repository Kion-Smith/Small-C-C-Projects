// Tetris.cpp : Defines the entry point for the console application.
// based of a youtbe tutorial by OneLoneCoder can be found at https://www.youtube.com/watch?v=8OK8_tHeCIA&index=3&list=LL8pDyb4hQUBUbgOxTT9lhlA&t=691s
// I want to improve on this and add the hold items to the side of the screen and possibley make a main menu
#include "stdafx.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <thread>
#include <vector>

int rotatePiece(int, int, int);
bool validPieceLoc(int, int, int, int);
char convetPieceName(int);

using namespace std;
wstring pieces[7];

int screenWidth = 80;			
int screenHeight = 30;			

int boardWidth = 12;
int boardHeight = 18;

unsigned char *board = nullptr;


int main()
{

	// I
	pieces[0].append(L"..X...X...X...X.");

	// Z
	pieces[1].append(L"..X..XX..X......");

	// S
	pieces[2].append(L".X...XX...X.....");

	// O
	pieces[3].append(L".....XX..XX.....");

	// T
	pieces[4].append(L"..X..XX...X.....");

	//L
	pieces[5].append(L".....XX...X...X.");

	//J
	pieces[6].append(L"..X...X..XX.....");

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

	int curPiece = rand()%7;
	int nextPiece = rand() % 7;
	int holdPiece = -1;
	int curRotation = 0;
	int curX = boardWidth/2;
	int curY = 0;

	bool bKey[5];
	bool isRotating;
	bool isHolding = false;
	bool hasHolded = false;

	int speed = 20;
	int speedCount = 0;
	bool gravity = false;

	int scoredPieces = 0;
	int score = 0;
	vector<int> lines;




	while (isRunning)
	{
		//speed
		this_thread::sleep_for(50ms);
		speedCount++;
		gravity = (speedCount == speed);

		//key detecrtion
		for (int k = 0; k < 5; k++)
		{
			//hex for the keys
			bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28ZX"[k]))) != 0;
		}
		//movement
		curX += (bKey[0] && validPieceLoc(curPiece, curRotation, curX + 1, curY)) ? 1 : 0;
		curX -= (bKey[1] && validPieceLoc(curPiece, curRotation, curX - 1, curY)) ? 1 : 0;
		curY += (bKey[2] && validPieceLoc(curPiece, curRotation, curX, curY + 1)) ? 1 : 0;

		//rotations 
		if (bKey[3])
		{
			curRotation += (isRotating && validPieceLoc(curPiece, curRotation + 1, curX, curY)) ? 1 : 0;
			isRotating = false;
		}
		else
		{
			isRotating = true;
		}

		//switch keys for holding and letting go
		if (bKey[4] && !hasHolded && !isHolding)
		{
			hasHolded = true;

			curX = boardWidth / 2;
			curY = 0;

			holdPiece = curPiece;
			curPiece = nextPiece;

			isHolding = true;

			
		}
		else if (bKey[4] && !hasHolded && isHolding)
		{
			hasHolded = true;

			curX = boardWidth / 2;
			curY = 0;

			int temp = curPiece;
			curPiece = holdPiece;
			holdPiece = temp;

			isHolding = true;
		}
	
		//gravity
		if (gravity)
		{

			

			if (validPieceLoc(curPiece, curRotation, curX, curY + 1))
			{
				curY++;
				
			}
			else
			{
				for (int px = 0; px < 4; px++)
				{
					for (int py = 0; py < 4; py++)
					{
						if (pieces[curPiece][rotatePiece(px, py, curRotation)] == L'X')
						{
							board[(curY + py) * boardWidth + (curX + px)] = curPiece + 1;
						
							
						}
					}
					
				}

				//speed changes the number of game ticks
				scoredPieces++;
				if (scoredPieces % 10 == 0)
				{	
					if (speed >= 10)
					{
						speed--;
					}
				}
				
				//once scored stop holding
				hasHolded = false;

				
				for (int py = 0; py < 4; py++)
				{
					if (curY + py < boardHeight - 1)
					{
						bool bLine = true;
						for (int px = 1; px < boardWidth - 1; px++)
							bLine &= (board[(curY + py) * boardWidth + px]) != 0;

						if (bLine)
						{
							// Remove Line, set to =
							for (int px = 1; px < boardWidth - 1; px++)
								board[(curY + py) * boardWidth + px] = 8;
								lines.push_back(curY + py);

								
						}
					}

					
					
				}

				score += 25;
				if (!lines.empty())
				{
					score += (1 << lines.size()) * 100;
				}

				curPiece = nextPiece;
				nextPiece = rand() % 7;

				curX = boardWidth / 2;
				curY = 0;
				curRotation = 0;
				

				isRunning = validPieceLoc(curPiece, curRotation, curX, curY);
		 
			}
			speedCount = 0;
		}

		for (int x = 0; x < boardWidth; x++)
		{
			for (int y = 0; y < boardHeight; y++)
			{
				screen[(y + 2)*screenWidth + (x + 2)] = L" ABCDEFG=#"[board[y*boardWidth + x]];
			}
		}

		for (int px = 0; px < 4; px++)
		{
			for (int py = 0; py < 4; py++)
			{
				if (pieces[curPiece][rotatePiece(px, py, curRotation)] == L'X')
				{
					screen[(curY + py + 2)*screenWidth + (curX + px + 2)] = curPiece + 65;
				}
			}
		}

		
		swprintf_s(&screen[2 * screenWidth + boardWidth + 6], 16, L"SCORE: %8d", score);
		swprintf_s(&screen[6 * screenWidth + boardWidth + 6], 16, L"Next: %9c", convetPieceName(nextPiece));
		swprintf_s(&screen[8 * screenWidth + boardWidth + 6], 16, L"Hold: %9c", convetPieceName(holdPiece));


		if (!lines.empty() )
		{
			WriteConsoleOutputCharacter(Console, screen, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten);
			this_thread::sleep_for(400ms);

			for (auto &v : lines)
			{
				for (int px = 1; px < boardWidth - 1; px++)
				{
					for (int py = v; py > 0; py--)
					{
						board[py*boardWidth + px] = board[(py - 1)*boardWidth + px];
					}

					board[px] = 0;
				}
			}

			lines.clear();
		}

		WriteConsoleOutputCharacter(Console, screen, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten);
		
	}
	CloseHandle(Console);
	cout << "Game Over \n SCORE ::" << score << endl;
	system("pause");

	return 0;

}

bool validPieceLoc(int curPiece, int rotation, int posX ,int posY)
{
	for (int px = 0; px < 4; px++)
	{
		for (int py = 0; py < 4; py++)
		{
			int pi = rotatePiece(px, py, rotation);

			int fi = (posY + py)*boardWidth + (posX + px);

			if ( (posX+px >=0) && (posX +px <boardWidth) )
			{
				if ((posY + py >= 0) && (posY + py < boardHeight))
				{
					if (pieces[curPiece][pi] == L'X' && board[fi] != 0)
					{
						return false;
					}
				}
			}
		}
	}

	return true;
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

char convetPieceName(int pieceName)
{
	char pieceString = '\0';
	switch (pieceName)
	{
		case 0:
			pieceString = 'I';
			break;
		case 1:
			pieceString = 'Z';
			break;
		case 2:
			pieceString = 'S';
			break;
		case 3:
			pieceString = 'O';
			break;
		case 4:
			pieceString = 'T';
			break;
		case 5:
			pieceString = 'L';
			break;
		case 6:
			pieceString = 'J';
			break;
	}
	return pieceString;
}
