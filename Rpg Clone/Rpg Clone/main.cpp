#include <iostream>
#include <windows.h>
#include <thread>

using namespace std;
bool checkNextMove(int, int);

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
			playField[y*playFieldWidth + x] = ( x==0 || y==0 ||x == playFieldWidth - 1 || y == playFieldHeight - 1) ? 0 : (rand() %2)+1;
			
		}
	}

	wchar_t *screen = new wchar_t[consoleWidth*consoleHeight];
	wchar_t *battleScreen = new wchar_t[consoleWidth*consoleHeight];

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
		this_thread::sleep_for(50ms);

		for (int k = 0; k < 4; k++)
		{													// left,up,right,down		
			keys[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x25\x26\x27\x28"[k]))) != 0;
		}

		curX -= (keys[0] && checkNextMove(curX-1,curY) ) ? 1 : 0; //25 (Left)
		curY -= (keys[1] && checkNextMove(curX, curY-1)) ? 1 : 0; //26 (Up)
		curX += (keys[2] && checkNextMove(curX + 1, curY)) ? 1 : 0; //27 (Right)
		curY += (keys[3] && checkNextMove(curX, curY+1)) ? 1 : 0; //28 (Down)


		for (int x = 0; x < playFieldWidth; x++)
		{
			for (int y = 0; y < playFieldHeight; y++)
			{
				screen[(y+2)*consoleWidth + (x+4)] = L"\u2588\u2591 #"[playField[y*playFieldWidth + x]];
				
			}
		}
	


		if (screen[curY*consoleWidth + curX] == L'\u2591')
		{
			//CloseHandle(console);
			WriteConsoleOutputCharacter(console, battleScreen, consoleWidth*consoleHeight, { 0,0 }, &dwBytesWritten);
		}
		else
		{
			screen[curY*consoleWidth + curX] = L'\u263B';
			WriteConsoleOutputCharacter(console, screen, consoleWidth*consoleHeight, { 0,0 }, &dwBytesWritten);
		}

		//drawing player
		

		

	}

	return 0;
}

//going to add collsion to other obsticals later
bool checkNextMove(int posX, int posY)
{
	if (posX >= 0+5 && posX < playFieldWidth+3)
	{
		if (posY >= 0+3 && posY < playFieldHeight+1)
		{
			return true;
		}
	}
	
	return false;


}


