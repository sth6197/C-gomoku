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
			board[position->x][position->y] = (player == BLACK_S) ? '●' : '○';
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

		printf("오목 게임\n");
		printf("2인의 플레이어가 서로 번갈아가면서 플레이합니다.\n");
		printf("먼저 5개의 돌을 일렬로 만드는 쪽이 승리합니다.\n");
		printf("시작하려면 아무 키나 눌러주세요\n");

		ch = _getch();

		system("cls");


		Board(board);

		printf("조작법 : 이동 - 방향키, 돌놓기 - 스페이스바\n");
		printf("게임 종료 : ESC\n");

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
														  
	for (int i = 0; i < 20; i++)	// 가로
	{
		for (int j = 0; j < 19; j++)	// 세로
		{
			if (s[i][j] == 0)
			{
				printf(" ┏ ");
			}
			else if (s[i][j] == 1)
			{
				printf(" ━ ");
			}
			else if (s[i][j] == 2)
			{
				printf(" ┓ ");
			}
			else if (s[i][j] == 3)
			{
				printf(" ┃ ");
			}
			else if (s[i][j] == 4)
			{
				printf(" ╋ ");
			}
			else if (s[i][j] == 5)
			{
				printf(" ┗ ");
			}
			else if (s[i][j] == 6)
			{
				printf(" ┛ ");
			}
		}
		printf("\n");
	}
}

 