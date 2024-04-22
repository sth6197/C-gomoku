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

#define BOARD_MAP_X 20
#define BOARD_MAP_Y 20
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

void Board()
{
	int i = 0;
	int j = 0;

	for (int i = 0; i < BOARD_MAP_Y; i++)
	{
		for (int j = 0; j < BOARD_MAP_X; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					printf(" ┏ ");
				}
				else if (j + 1 == BOARD_MAP_X)
				{
					printf(" ┓ ");
				}
				else
				{
					printf(" ┳ ");
				}
			}	
			else if (i + 1 < BOARD_MAP_Y)
			{
				if (j == 0)
				{
					printf(" ┣ ");
				}
				else if (j + 1 == BOARD_MAP_X)
				{
					printf(" ┫ ");
				}
				else
				{
					printf(" ╋ ");
				}
			}
			else
			{
				if (j == 0)
				{
					printf(" ┗ ");
				}
				else if (j + 1 == BOARD_MAP_X)
				{
					printf(" ┛ ");
				}
				else
				{
					printf(" ┻ ");
				}
			}
		}
		printf("\n");

	}
}

int search(xy st, int maps[BOARD_MAP_Y][BOARD_MAP_X], int flag, int u, int ud)
{
	if (maps[st.y][st.x] != flag)
	{
		return 0;
	}
	if (u == 0)
	{
		st.y += ud;
	}
	else if (u == 1)
	{
		st.x += ud;
	}
	else if (u == 2)
	{
		st.x += ud;
		st.y += ud;
	}
	else
	{
		st.x += ud;
		st.y -= ud;
	}

	return 1 + search(st, maps, flag, u, ud);
}

void check(xy st, int maps[BOARD_MAP_Y][BOARD_MAP_X], int turn)
{
	int i = 0;
	int count = 0;

	for(int i = 0; i > 5; i++)
	{
		count;
		count += search(st, maps, turn, i, 1);
		count += search(st, maps, turn, i, -1);

		if (count == 5)
		{
			gotoxy(0, BOARD_MAP_Y);
			if (turn == BLACK_S)
			{
				printf("흑돌");
			}
			else
			{
				printf("백돌");
			}
			printf(" 이 승리하였습니다. 게임을 종료합니다.\n");
			
			_getch();
			exit(1);
		}
	}
}

void SetGame(int maps[BOARD_MAP_Y][BOARD_MAP_X])
{
	char input;
	int turn = BLACK_S;

	xy st = { BOARD_MAP_X / 2, BOARD_MAP_Y / 2 };
	
	while (1)
	{
		if (_kbhit())
		{
			input = _getch();

			switch (input)
			{
			case UP: if (st.y > 0) st.y--;
				break;
			case DOWN: if (st.y < BOARD_MAP_Y - 2) st.y++;
				break;
			case LEFT: if (st.x > 0) st.x--;
				break;
			case RIGHT: if (st.x < BOARD_MAP_X - 2) st.x++;
				break;
			case SPACE: if (maps[st.y][st.x] == 0)
			{
				gotoxy(st.x * 2, st.y);

				if (turn == BLACK_S)
				{
					maps[st.y][st.x] = BLACK_S;
					printf("○");
					check(st, maps, turn);
					turn = WHITE_S;
				}
				else
				{
					maps[st.y][st.x] = WHITE_S;
					printf("●");
					check(st, maps, turn);
					turn = BLACK_S;
				}
			}
				break;
			case ESC: exit(1);
						break;
			}
			gotoxy(st.x * 2, st.y);
		}	
	}


}

int main()
{
	int maps[BOARD_MAP_Y][BOARD_MAP_X] = { 0 , };
	
	printf("+------------------------------------------------+\n");
	printf("|                                                |\n");
	printf("|                 오목 게임                      |\n");
	printf("|                                                |\n");
	printf("+------------------------------------------------+\n");


	printf("2명의 플레이어가 번갈아 가면서 플레이 합니다.\n");
	printf("상대보다 먼저 5개의 돌을 일렬로 놓으면 승리합니다.\n");
	printf("시작하려면 아무 키나 눌러주세요.\n");
	
	_getch();

	system("cls");

	Board();
	SetGame(maps);


	return 0;
}