#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#define BLACK_STONE "��"
#define WHITE_STONE "��"

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define SPACE 32
#define ENTER 13

void gotoxy(int x, int y)
{
	COORD pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int gamestart = 0;


void Board(); // ������
void gameend(); // ���� ����
void Cursor(); // ����� �̵�
void R_Cursor(); // �����, ����
void reset_Board();	// ������ �ʱ�ȭ



int main()
{
	
	while (1)
	{
		Board();
		system("cls");



	}



	return 0;
}

void Board()
{
	int i = 0;
	int j = 0;
	char s[70][70]= {
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7},
		{ 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6} };

	for (int i = 0; i < 20; i++)	// ����
	{
		for (int j = 0; j < 19; j++)	// ����
		{
			if (s[i][j] == 0)
			{
				printf(" �� ");
			}
			else if (s[i][j] == 1)
			{
				printf(" �� ");
			}
			else if (s[i][j] == 2)
			{
				printf(" �� ");
			}
			else if (s[i][j] == 3)
			{
				printf(" �� ");
			}
			else if (s[i][j] == 4)
			{
				printf(" �� ");
			}
			else if (s[i][j] == 5)
			{
				printf(" �� ");
			}
			else if (s[i][j] == 6)
			{
				printf(" �� ");
			}
			else if (s[i][j] == 7)
			{
				printf(" �� ");
			}
		}
		printf("\n");
	}
}

