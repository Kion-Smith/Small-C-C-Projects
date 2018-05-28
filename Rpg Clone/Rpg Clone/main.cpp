#include <iostream>
#include <windows.h>

bool checkNextMove(int, int, int);

int playFieldWidth = 50;
int playFieldHeight = 20;


int consoleWidth = 80;
int consoleHeight =50;


unsigned char *playField = nullptr;


int main()
{

	playField = new unsigned char[playFieldWidth*playFieldHeight];

	for (int x = 0; x < playFieldWidth; x++)
	{
		for (int y = 0; y < playFieldHeight; y++)
		{
			playField[y*playFieldWidth + x] = ( x==0 || y==0 ||x == playFieldWidth - 1 || y == playFieldHeight - 1) ? 2 : 1;
		}
	}

	wchar_t *screen = new wchar_t[consoleWidth*consoleHeight];
	for (int i = 0; i < consoleWidth*consoleHeight; i++)
	{
		screen[i] = L' ';
	}



	HANDLE console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,0,NULL,CONSOLE_TEXTMODE_BUFFER,NULL );
	SetConsoleActiveScreenBuffer(console);
	DWORD dwBytesWritten = 0;

	//game loop items
	bool isRunning = true;
	bool keys[4];

	// player items
	int playerChar = 3;
	int curX = playFieldWidth/ 2;
	int curY = playFieldHeight/2;

	while (isRunning)
	{

		for (int k = 0; k < 4; k++)
		{
																// left,up,right,down		
			keys[4] = (0x8000 & GetAsyncKeyState((unsigned char)("\x25\x26\x27\x28"[k]))) != 0;
		}

		for (int x = 0; x < playFieldWidth; x++)
		{
			for (int y = 0; y < playFieldHeight; y++)
			{
				screen[(y+2)*consoleWidth + (x+4)] = L" \u2591\u2588"[playField[y*playFieldWidth + x]];
			}
		}

		//this will be player movement 
		if (false) //add some way to check player movements
		{

		}
		else
		{

		}
		//drawing player
		screen[curY*consoleWidth + curX] = L'\u263B';

		WriteConsoleOutputCharacter(console, screen, consoleWidth*consoleHeight, { 0,0 } ,&dwBytesWritten);
	}

	


	return 0;
}

