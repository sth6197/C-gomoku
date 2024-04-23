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
#define q 113

#define BOARD_MAP_X 20		// 오목판 가로
#define BOARD_MAP_Y 20		// 오목판 세로
#define BLACK_S 1			// 흑돌
#define WHITE_S 2			// 백돌

typedef struct              // 좌표
{
	int x;
	int y;
}xy;

void CursorView()
{
	CONSOLE_CURSOR_INFO cursorinfo = { 0, };
	cursorinfo.dwSize = 1;
	cursorinfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorinfo);
}
void CursorView2()
{
	CONSOLE_CURSOR_INFO cursorinfo = { 0, };
	cursorinfo.dwSize = 1;
	cursorinfo.bVisible = TRUE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorinfo);
}

void gotoxy(int x, int y)
{
	COORD pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Board()			// 오목판 함수
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
					printf(" ┌");
				}
				else if (j + 1 == BOARD_MAP_X)
				{
					printf(" ┐");
				}
				else
				{
					printf(" ┬");
				}
			}	
			else if (i + 1 < BOARD_MAP_Y)
			{
				if (j == 0)
				{
					printf(" ├");
				}
				else if (j + 1 == BOARD_MAP_X)
				{
					printf(" ┤");
				}
				else
				{
					printf(" ┼");
				}
			}
			else
			{
				if (j == 0)
				{
					printf(" └");
				}
				else if (j + 1 == BOARD_MAP_X)
				{
					printf(" ┘");
				}
				else
				{
					printf(" ┴");
				}
			}
		}
		printf("\n");
		
	}
	printf("조작법 : 방향키 - 이동, 스페이스바 - 돌놓기\n");
	printf("게임 종료 :  ESC\n");
	printf("다시 시작: q\n\n");
	printf("게임을 다시 시작했을 경우 q를 두 번 이상 눌러주세요.\n");
}

int search(xy st, int maps[BOARD_MAP_Y][BOARD_MAP_X], int flag, int u, int ud)		// 위, 아래, 좌, 우, 대각선 판정
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

void check(xy st, int maps[BOARD_MAP_Y][BOARD_MAP_X], int turn)		// 승패 판정
{
	
	int i = 0;
	int count = 0;

	for(int i = 0; i < 4; i++)
	{
		count = 0;
		count += search(st, maps, turn, i, 1);
		count += search(st, maps, turn, i, -1);

		if (count == 6)
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
			printf(" 이 승리하였습니다.\n");
			
			CursorView();	// 게임 판정 났을 때 커서 숨김
		}
	}
}

void SetGame(int maps[BOARD_MAP_Y][BOARD_MAP_X])		// 키보드, 플레이어 턴 함수
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
			case DOWN: if (st.y < BOARD_MAP_Y - 1) st.y++;
				break;
			case LEFT: if (st.x > 0) st.x--;
				break;
			case RIGHT: if (st.x < BOARD_MAP_X - 1) st.x++;
				break;
			case SPACE: if (maps[st.y][st.x] == 0)
			{
				gotoxy(st.x * 2, st.y);

				if (turn == BLACK_S)		// 흑돌 턴
				{
					maps[st.y][st.x] = BLACK_S;
					printf("○");
					check(st, maps, turn);
					turn = WHITE_S;
				}
				else                         // 백돌 턴
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
			case 113:
				return 0;
				break;
			}
			gotoxy(st.x * 2, st.y);
		}	
	}


}

void ResetGame(int maps[BOARD_MAP_Y][BOARD_MAP_X])
{
	for (int i = 0; i < BOARD_MAP_Y; i++)
	{
		for (int j = 0; j < BOARD_MAP_X; j++)
		{
			maps[i][j] = 0;
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
	
	while (1)
	{
		_getch(q);

		system("cls");

		Board();
		SetGame(maps);
		CursorView2();	// 다시 커서 표시
		ResetGame(maps);	
	}
	return 0;
}