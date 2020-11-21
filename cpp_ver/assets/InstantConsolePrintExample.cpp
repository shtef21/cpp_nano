#include <iostream>
#include <vector>
#include <utility>
using namespace std;

#include <stdio.h>
#include <Windows.h>

int nScreenWidth = 120;			// Console Screen Size X (columns)
int nScreenHeight = 40;			// Console Screen Size Y (rows)
int nMapWidth = 16;				// World Dimensions
int nMapHeight = 16;

int main()
{
	// Create Screen Buffer
	wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

		// "D" pressed
		if (GetAsyncKeyState((unsigned short)'D') & 0x8000);
	
	// Display Frame
		screen[nScreenWidth * nScreenHeight - 1] = '\0'; 

	WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}

	return 0;
}
