#include <iostream>
#include <windows.h>
int playFieldWidth = 20;
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
			//playField[y*playFieldWidth + x] =
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

	bool isRunning = true;

	while (isRunning)
	{
		for (int x = 0; x < playFieldWidth; x++)
		{
			for (int y = 0; y < playFieldHeight; y++)
			{
				//screen[(y)*playFieldWidth + (x)] = L" ABCDEFG=#"[playField[y*playFieldWidth + x]];
			}
		}

		WriteConsoleOutputCharacter(console, screen, consoleWidth*consoleHeight, { 0,0 } ,&dwBytesWritten);
	}

	


	return 0;
}