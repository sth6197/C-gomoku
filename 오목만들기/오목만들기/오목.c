#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>
#include <Digitalv.h>

#pragma comment(lib, "winmm.lib")

MCI_OPEN_PARMS openBgm;
MCI_PLAY_PARMS playBgm;
DWORD m_dwDeviceID;
MCI_OPEN_PARMS opengomokusound;
MCI_PLAY_PARMS playgomokusound;

int dwID;

#define UP 72			// 방향키 ↑
#define LEFT 75			// 방향키 ←
#define RIGHT 77		// 방향키 →
#define DOWN 80			// 방향키 ↓
#define SPACE 32		// 스페이스바
#define ENTER 13		// 엔터키
#define ESC 27			// ESC키
#define q 113			// q키

#define BOARD_MAP_X 20		// 오목판 가로
#define BOARD_MAP_Y 20		// 오목판 세로
#define BLACK_S 1			// 흑돌
#define WHITE_S 2			// 백돌

typedef struct              // 좌표 함수 구조체
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
	COORD pos = { x + 1, y };
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

void playingbgm()		// 배경음
{
	openBgm.lpstrElementName = "gomokubgm.mp3";			// 파일 열기
	openBgm.lpstrDeviceType = "mpegvideo";				// mp3 형식 지정
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);	// 배경음 반복 재생
}

void playingTaksound()	// 오목알 착수 효과음
{
	opengomokusound.lpstrElementName = "gomokuegg.mp3";		// 파일 열기
	opengomokusound.lpstrDeviceType = "mpegvideo";			// mp3 형식 지정
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&opengomokusound);
	dwID = opengomokusound.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_RESUME, (DWORD)(LPVOID)&opengomokusound);	// 효과음을 한 번 씩만 재생
}

void Board()			// 오목판 함수
{
	int i = 0;
	int j = 0;
	
	// 반복문과 조건문을 통해 오목판 그리기
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
	printf("\n\n");
	printf("조작법 : 키보드 방향키 - 커서 이동, 스페이스바 - 돌놓기\n");
	printf("다시 시작 : Q\n");
	printf("게임 종료 : ESC\n\n");
	printf("승부가 났다면 Q를 두 번 이상 눌러주세요.\n\n");
}

int search(xy st, int maps[BOARD_MAP_Y][BOARD_MAP_X], int flag, int u, int ud)	// flag(검색하려는 돌 색깔),  u(검색할 방향)
{																				// ud(방향 변수, 양수이면 오른쪽 또는 아래로 이동, 음수이면 왼쪽 또는 위로 이동)
	if (maps[st.y][st.x] != flag)												// 해당 턴 플레이어의 돌색깔을 구분하고, 돌색깔이 다르다면 검사 계속 진행 
	{
		return 0;
	}
	if (u == 0)			// 위, 아래
	{
		st.y += ud;
	}
	else if (u == 1)	// 좌, 우
	{
		st.x += ud;
	}
	else if (u == 2)	// 왼쪽 위 -> 오른쪽 아래
	{
		st.x += ud;
		st.y += ud;
	}
	else                // 오른쪽 위 -> 왼쪽 아래
	{
		st.x += ud;
		st.y -= ud;
	}

	return 1 + search(st, maps, flag, u, ud);		
	// 현재 위치에서 주변 방향으로 한 칸씩 이동하면서 같은 색깔 돌찾기 -> 돌을 찾으면 그 지점부터 다시 주변 방향으로 돌찾기 
	// -> 반복하면서 돌 개수 세기 -> 돌을 찾으면 1씩 더해주기 -> 연속된 돌이 없거나 오목판 끝을 만나면 반복을 멈추고 돌 개수 값 반환
}

void check(xy st, int maps[BOARD_MAP_Y][BOARD_MAP_X], int turn)		// 승패 판정, turn(플레이어의 턴)
{
	int i = 0;
	int count = 0;

	for(int i = 0; i < 4; i++)						
	{
		count = 0;									// count 변수 초기화, 방향별 연속적인 돌 개수 저장(게임 시작시 search 함수가 돌아가며 초기화 값에 1이 더해짐)
		count += search(st, maps, turn, i, 1);		// search 함수 호출(돌을 놓은 위치에서 주변 돌을 검사하기 위해) -> st 변수에서 주어진 방향으로 돌 개수 검사, 오목판 배열, 플레이어 턴,
		count += search(st, maps, turn, i, -1);		// 방향을 나타내며 0~3의 값을 가지는 i 변수, 검사 중 빈 공간이나 상대방의 돌을 만날 시 검사 중단 및 -1, 같은 색깔 돌이면 검사 계속 진행 및 1)
													// search 함수를 통해 구해진 값을 count에 더하여 돌을 놓은 위치를 기준으로 주변의 연속적인 돌 개수 검사, 계산
		if (count == 6)								// 놓여진 돌 개수를 검사하고, 턴이 넘어가기 전에 값을 count에 저장하여 count의 값이 6이라면 해당 턴 플레이어의 승리
		{
			gotoxy(0, BOARD_MAP_Y);
			if (turn == BLACK_S)
			{
				printf("흑돌 승리!\a");
			}
			else
			{
				printf("백돌 승리!\a");
			}
			CursorView();	// 게임 판정 났을 때 커서 숨김
		}
	}
}

void SetGame(int maps[BOARD_MAP_Y][BOARD_MAP_X])		// 키보드, 플레이어 턴 함수
{
	char input;
	int turn = BLACK_S;									// 처음 시작 턴은 항상 흑돌이 먼저 하도록 한다.

	xy st = { BOARD_MAP_X / 2, BOARD_MAP_Y / 2 };		// 오목판 전체 가로/2, 세로/2 로 나눈 위치 값에 초기 돌놓을 위치 지정
	
	while (1)
	{
		if (_kbhit())												// 키보드 입력
		{
			input = _getch();

			switch (input)
			{
			case UP: if (st.y > 0) st.y--;							// y 좌표가 0보다 클 때 까지만 올라가도록 조건문
				break;
			case DOWN: if (st.y < BOARD_MAP_Y-1) st.y++;			// BOARD_MAP_Y의 -1 까지만 내려가도록 조건문
				break;
			case LEFT: if (st.x > 0) st.x--;						// x 좌표가 0보다 클 때 까지만 왼쪽으로 가도록 조건문
				break;
			case RIGHT: if (st.x < BOARD_MAP_X-1) st.x++;			// BOARD_MAP_X의 -1 까지만 오른쪽으로 가도록 조건문
				break;
			case SPACE: if (maps[st.y][st.x] == 0)					// 해당 위치 값이 0이라면 SPACE바 입력으로 해당 턴 플레이어의 값 입력, 돌이 겹친다면 입력이 안되도록 처리
			{
				gotoxy(st.x * 2, st.y);
				
				if (turn == BLACK_S)		// 흑돌 턴
				{
					maps[st.y][st.x] = BLACK_S;		// 흑돌 돌놓기 좌표, maps의 배열에 위치 값(흑돌 1, 백돌 2의 값)을 플레이어의 돌 색깔에 맞게 변경 및 저장
					playingTaksound();
					printf("○");
					check(st, maps, turn);			// 돌을 일렬로 5개 놓았는지, 겹치는지 검사
					turn = WHITE_S;					// 승리 판정이 아니고 문제없이 돌을 놓았다면 백돌로 턴 넘김
				}
				else                         // 백돌 턴
				{
					maps[st.y][st.x] = WHITE_S;		// 백돌 돌놓기 좌표, maps의 배열에 위치 값(흑돌 1, 백돌 2의 값)을 플레이어의 돌 색깔에 맞게 변경 및 저장
					playingTaksound();
					printf("●");
					check(st, maps, turn);			// 돌을 일렬로 5개 놓았는지, 겹치는지 검사
					turn = BLACK_S;					// 승리 판정이 아니고 문제없이 돌을 놓았다면 흑돌로 턴 넘김
				}
			}
				break;
			case ESC: exit(0);						// ESC키를 누르면 콘솔창 종료
						break;
			case q:
				return;
			}
			gotoxy(st.x * 2, st.y);					// 오목판 열 사이의 공백을 이동하고 정확한 위치에 착수를 위해 st.x를 2를 곱해준다.
		}											// 만약 나누기 2를 한다면 정확한 좌표로 커서가 이동하지 않고 어긋나게 되며, 착수 위치도 행열에 맞지 않고 어긋나게 된다.
	}
}

void ResetGame(int maps[BOARD_MAP_Y][BOARD_MAP_X])	// 게임 재시작 시 오목판 다시 그리기
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
	system("title 오목_ver0.1");					// 게임 제목
	system("mode con:cols=57 lines=30");		// col 가로 길이, lines 세로 길이

	playingbgm();

	int maps[BOARD_MAP_Y][BOARD_MAP_X] = { 0 , };
	
	color(11);
	printf("+------------------------------------------------+\n");
	printf("|                                                |\n");
	printf("|                   오목 게임                    |\n");
	printf("|                                                |\n");
	printf("+------------------------------------------------+\n\n");

	color(15);
	printf("2명의 플레이어가 번갈아 가면서 플레이 합니다.\n");
	printf("상대보다 먼저 5개의 돌을 일렬로 놓으면 승리합니다.\n");
	printf("시작하려면 아무 키나 눌러주세요.\n");
	
	_getch();

	system("cls");

	Board();
	SetGame(maps);

	while (1)				// 재시작 할 경우 다시 보드판과 게임 설정을 불러옴
	{	
		_getch();
		
		system("cls");
		
		Board();
		
		SetGame(maps);
		
		CursorView2();		// 다시 커서 표시
		
		ResetGame(maps);
	}

	return 0;
}