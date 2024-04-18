#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define BOARD 19
#define BLACK_STONE "¡Û"
#define WHITE_STONE "¡Ü"

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define SPACE 32

void gotoxy(int x, int y)
{
	COORD pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
 
int main()
{



	return 0;
}