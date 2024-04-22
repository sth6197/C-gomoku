#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define SPACE 32
#define ENTER 13
#define ESC 27

#define BLACK_S 1
#define WHITE_S 2

typedef struct
{
	int x;
	int y;
}xy;

void gotoxy(int x, int y)
{
	COORD pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void move_stone(int player, xy *position, char board[19][19])
{
	if (position->x >= 0 && position->x < 19 && position->y >= 0 && position->y < 19)
	{
		if (board[position->x][position->y] == ' ')
		{
			board[position->x][position->y] = (player == BLACK_S) ? '��' : '��';
		}
	}
}


void Board(board);

int main()
{
	char ch;
	xy position = { 0, 0 };
	int turn = BLACK_S;
	char board[19][19];
	memset(board, ' ', sizeof(board));

	while (1)
	{

		printf("���� ����\n");
		printf("2���� �÷��̾ ���� �����ư��鼭 �÷����մϴ�.\n");
		printf("���� 5���� ���� �Ϸķ� ����� ���� �¸��մϴ�.\n");
		printf("�����Ϸ��� �ƹ� Ű�� �����ּ���\n");

		ch = _getch();

		system("cls");


		Board(board);

		printf("���۹� : �̵� - ����Ű, ������ - �����̽���\n");
		printf("���� ���� : ESC\n");

		Sleep(100);

		while (1)
		{
			char key = _getch();

			if (key == ESC)
			{
				return 0;
			}
			else if (key == SPACE)
			{
				move_stone(turn, &position, board);
				turn = (turn == BLACK_S) ? WHITE_S : BLACK_S;
				break;
			}
			else if (key == UP && position.y > 0)
			{
				position.y--;
			}
			else if (key == DOWN && position.y < 18)
			{
				position.y++;
			}
			else if (key == LEFT && position.x > 0)
			{
				position.x--;
			}
			else if (key == RIGHT && position.x < 18)
			{
				position.x++;
			}



		}
		
	}



	return 0;
}

void Board(char board[19][19])
{
	int i = 0;
	int j = 0;
	char s[70][70]= {
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3},
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3},
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
		}
		printf("\n");
	}
}

 