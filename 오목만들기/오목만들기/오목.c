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

void CursorView()					// 커서 숨김 함수
{
	CONSOLE_CURSOR_INFO cursorinfo = { 0, };
	cursorinfo.dwSize = 1;
	cursorinfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorinfo);
}
void CursorView2()					// 커서 보이기 함수
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

void color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	/*
	검은색 0, 파란색 1, 초록색 2, 옥색 3, 빨간색 4, 자주색 5, 노란색 6, 흰색 7
	회색 8, 연파랑 9, 연초록 10, 연한 옥색 11, 연빨 12, 연한 자주 13, 연노랑 14, 진한 흰색 15
	*/
}

void Board()			// 오목판 함수
{
	int i = 0;
	int j = 0;
	
	color(7);
	for (int i = 0; i < BOARD_MAP_Y; i++)
	{
		for (int j = 0; j < BOARD_MAP_X; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					printf(" ┏");
				}
				else if (j + 1 == BOARD_MAP_X)
				{
					printf(" ┓");
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
					printf(" ┗");
				}
				else if (j + 1 == BOARD_MAP_X)
				{
					printf(" ┛");
				}
				else
				{
					printf(" ┴");
				}
			}
		}
		printf("\n");
	}
	printf("조작법 : 키보드 방향키 - 이동, 스페이스바 - 돌놓기\n");
	printf("다시 시작: Q\n\n");
	printf("게임 종료 :  ESC\n");
	printf("실행 후 처음 게임을 다시 시작했을 경우 Q를 두 번 이상 눌러주세요.\n");
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
				printf("흑돌 승리!");
			}
			else
			{
				printf("백돌 승리!");
			}
			CursorView();	// 게임 판정 났을 때 커서 숨김
			
			//Sleep(3000);
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

void ResetGame(int maps[BOARD_MAP_Y][BOARD_MAP_X])				// 게임 재시작시 보드 다시 그리기
{
	for (int i = 0; i < BOARD_MAP_Y; i++)
	{
		for (int j = 0; j < BOARD_MAP_X; j++)
		{
			maps[i][j] = 0;
		}
	}
}

//	void Restartquestion()
//	{
//		color(14);
//		printf("게임을 다시 시작하시려면 Q를 눌러주세요.\n");
//		
//		_getch();
//	}


int main()
{
	system("title 오목");
	system("mode con:cols=55 lines=30");		// col 가로, lines 세로

	int maps[BOARD_MAP_Y][BOARD_MAP_X] = { 0 , };
	
	color(9);
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
		_getch();
		
		system("cls");

		Board();
		SetGame(maps);
		
		CursorView2();	// 다시 커서 표시
		
		ResetGame(maps);
	}

	return 0;
}