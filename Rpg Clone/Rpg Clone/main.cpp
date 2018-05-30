#include <iostream>
#include <windows.h>
#include <thread>

using namespace std;
void startBattleAnimation(HANDLE eventConsole, wchar_t *pointer, DWORD bytes);
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
		battleScreen[i] = L' ';
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

	bool ranAnimation = false;

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
	

		//maybe convert to a switch stament?
		//need to stop player controll of character
		//need alg to draw box with unicode characters
		if (screen[curY*consoleWidth + curX] == L'\u2591')
		{
			if (!ranAnimation)
			{
				for (int i = 2; i > 0; i--)
				{
					startBattleAnimation(console, battleScreen, dwBytesWritten);
					this_thread::sleep_for(100ms);
					WriteConsoleOutputCharacter(console, screen, consoleWidth*consoleHeight, { 0,0 }, &dwBytesWritten);
				}
				screen[curY*consoleWidth + curX] = L'\u263B';	
				ranAnimation = true;
			}
			else
			{
				
				WriteConsoleOutputCharacter(console, battleScreen, consoleWidth*consoleHeight, { 0,0 }, &dwBytesWritten);
				
			}
			
				
			
			
			
		}
		else
		{
			ranAnimation = false;
			screen[curY*consoleWidth + curX] = L'\u263B';
			WriteConsoleOutputCharacter(console, screen, consoleWidth*consoleHeight, { 0,0 }, &dwBytesWritten);
		}
				
	} //end game loop

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

void startBattleAnimation(HANDLE eventConsole,wchar_t *screen,DWORD bytes)
{
	//make this run twice wit one loop not 2
	for (int x = 0; x < playFieldWidth; x++)
	{
		for (int y = 0; y < playFieldHeight; y++)
		{

			screen[(y + 2)*consoleWidth + (x + 4)] = L'.';
			
			
		}
	}
	this_thread::sleep_for(150ms);
	WriteConsoleOutputCharacter(eventConsole, screen, consoleWidth*consoleHeight, { 0,0 }, &bytes);
	
	for (int x = 0; x < playFieldWidth; x++)
	{
		for (int y = 0; y < playFieldHeight; y++)
		{

			screen[(y + 2)*consoleWidth + (x + 4)] = L' ';
			

		}
	}
	this_thread::sleep_for(150ms);
	WriteConsoleOutputCharacter(eventConsole, screen, consoleWidth*consoleHeight, { 0,0 }, &bytes);
	
}