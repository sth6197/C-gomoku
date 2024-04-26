#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <mmsystem.h>
#include <Digitalv.h>

#pragma comment(lib, "winmm.lib")

MCI_OPEN_PARMS openBgm;
MCI_PLAY_PARMS playBgm;
DWORD m_dwDeviceID;
MCI_OPEN_PARMS opengomokusound;
MCI_PLAY_PARMS playgomokusound;

int dwID;

#define UP 72			// ����Ű ��
#define LEFT 75			// ����Ű ��
#define RIGHT 77		// ����Ű ��
#define DOWN 80			// ����Ű ��
#define SPACE 32		// �����̽���
#define ENTER 13		// ����Ű
#define ESC 27			// ESCŰ
#define q 113			// qŰ

#define BOARD_MAP_X 20		// ������ ����
#define BOARD_MAP_Y 20		// ������ ����
#define BLACK_S 1			// �浹
#define WHITE_S 2			// �鵹

typedef struct              // ��ǥ �Լ� ����ü
{
	int x;
	int y;
}xy;

void CursorView()					// Ŀ�� ���� �Լ�
{
	CONSOLE_CURSOR_INFO cursorinfo = { 0, };
	cursorinfo.dwSize = 1;
	cursorinfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorinfo);
}
void CursorView2()					// Ŀ�� ���̱� �Լ�
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
	������ 0, �Ķ��� 1, �ʷϻ� 2, ���� 3, ������ 4, ���ֻ� 5, ����� 6, ��� 7
	ȸ�� 8, ���Ķ� 9, ���ʷ� 10, ���� ���� 11, ���� 12, ���� ���� 13, ����� 14, ���� ��� 15
	*/
}

void playingbgm()
{
	openBgm.lpstrElementName = "gomokubgm.mp3";			// ���� ����
	openBgm.lpstrDeviceType = "mpegvideo";				// mp3 ���� ����
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);	// ����� �ݺ� ���
}

void playingTaksound()
{
	opengomokusound.lpstrElementName = "gomokuegg.mp3";		// ���� ����
	opengomokusound.lpstrDeviceType = "mpegvideo";			// mp3 ���� ����
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&opengomokusound);
	dwID = opengomokusound.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_RESUME, (DWORD)(LPVOID)&opengomokusound);	// ȿ������ �� �� ���� ���

}

void Board()			// ������ �Լ�
{
	int i = 0;
	int j = 0;
	
	color(7);									// �ݺ����� ���ǹ��� ���� ������ �׸���
	for (int i = 0; i < BOARD_MAP_Y; i++)
	{
		for (int j = 0; j < BOARD_MAP_X; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					printf(" ��");
				}
				else if (j + 1 == BOARD_MAP_X)
				{
					printf(" ��");
				}
				else
				{
					printf(" ��");
				}
			}	
			else if (i + 1 < BOARD_MAP_Y)
			{
				if (j == 0)
				{
					printf(" ��");
				}
				else if (j + 1 == BOARD_MAP_X)
				{
					printf(" ��");
				}
				else
				{
					printf(" ��");
				}
			}
			else
			{
				if (j == 0)
				{
					printf(" ��");
				}
				else if (j + 1 == BOARD_MAP_X)
				{
					printf(" ��");
				}
				else
				{
					printf(" ��");
				}
			}
		}
		printf("\n");
	}
	printf("\n");
	printf("���۹� : Ű���� ����Ű - Ŀ�� �̵�, �����̽��� - ������\n");
	printf("�ٽ� ���� : Q\n");
	printf("���� ���� : ESC\n\n");
	printf("�ºΰ� ���ٸ� Q�� �� �� �̻� �����ּ���.\n\n");
}

int search(xy st, int maps[BOARD_MAP_Y][BOARD_MAP_X], int flag, int u, int ud)	// flag(�˻��Ϸ��� �� ����),  u(�˻��� ����)
{																				// ud(���� ����, ����̸� ������ �Ǵ� �Ʒ��� �̵�, �����̸� ���� �Ǵ� ���� �̵�)
	if (maps[st.y][st.x] != flag)		// �ش� �� �÷��̾��� �������� �����ϰ�, �������� �ٸ��ٸ� �˻� ��� ���� 
	{
		return 0;
	}
	if (u == 0)			// ��, �Ʒ�
	{
		st.y += ud;
	}
	else if (u == 1)	// ��, ��
	{
		st.x += ud;
	}
	else if (u == 2)	// ���� �� -> ������ �Ʒ�
	{
		st.x += ud;
		st.y += ud;
	}
	else                // ������ �� -> ���� �Ʒ�
	{
		st.x += ud;
		st.y -= ud;
	}

	return 1 + search(st, maps, flag, u, ud);		
	// ���� ��ġ���� �ֺ� �������� �� ĭ�� �̵��ϸ鼭 ���� ���� ��ã�� -> ���� ã���� �� �������� �ٽ� �ֺ� �������� ��ã�� 
	// -> �ݺ��ϸ鼭 �� ���� ���� -> ���� ã���� 1�� �����ֱ� -> ���ӵ� ���� ���ų� ������ ���� ������ �ݺ��� ���߰� �� ���� �� ��ȯ
}

void check(xy st, int maps[BOARD_MAP_Y][BOARD_MAP_X], int turn)		// ���� ����, turn(�÷��̾��� ��)
{
	int i = 0;
	int count = 0;

	for(int i = 0; i < 4; i++)						
	{
		count = 0;									// count ���� �ʱ�ȭ, ���⺰ �������� �� ���� ����(���� ���۽� search �Լ��� ���ư��� �ʱ�ȭ ���� 1�� ������)
		count += search(st, maps, turn, i, 1);		// search �Լ� ȣ��(���� ���� ��ġ���� �ֺ� ���� �˻��ϱ� ����) -> st �������� �־��� �������� �� ���� �˻�, ������ �迭, �÷��̾� ��,
		count += search(st, maps, turn, i, -1);		// ������ ��Ÿ���� 0~3�� ���� ������ i ����, �˻� �� �� �����̳� ������ ���� ���� �� �˻� �ߴ� �� -1, ���� ���� ���̸� �˻� ��� ���� �� 1)
													// search �Լ��� ���� ������ ���� count�� ���Ͽ� ���� ���� ��ġ�� �������� �ֺ��� �������� �� ���� �˻�, ���
		if (count == 6)								// ������ �� ������ �˻��ϰ�, ���� �Ѿ�� ���� ���� count�� �����Ͽ� count�� ���� 6�̶�� �ش� �� �÷��̾��� �¸�
		{
			gotoxy(0, BOARD_MAP_Y);
			if (turn == BLACK_S)
			{
				printf("�浹 �¸�!\a");
			}
			else
			{
				printf("�鵹 �¸�!\a");
			}
			CursorView();	// ���� ���� ���� �� Ŀ�� ����
		}
	}
}

void SetGame(int maps[BOARD_MAP_Y][BOARD_MAP_X])		// Ű����, �÷��̾� �� �Լ�
{
	char input;
	int turn = BLACK_S;									// ó�� ���� ���� �׻� �浹�� ���� �ϵ��� �Ѵ�.

	xy st = { BOARD_MAP_X / 2, BOARD_MAP_Y / 2 };		// ������ ��ü ����/2, ����/2, �ʱ� ������ ��ġ ����
	
	while (1)
	{
		if (_kbhit())												// Ű���� �Է�
		{
			input = _getch();

			switch (input)
			{
			case UP: if (st.y > 0) st.y--;							// y ��ǥ�� 0���� Ŭ �� ������ �ö󰡵��� ���ǹ�
				break;
			case DOWN: if (st.y < BOARD_MAP_Y-1) st.y++;			// BOARD_MAP_Y�� -1 ������ ���������� ���ǹ�
				break;
			case LEFT: if (st.x > 0) st.x--;						// x ��ǥ�� 0���� Ŭ �� ������ �������� ������ ���ǹ�
				break;
			case RIGHT: if (st.x < BOARD_MAP_X-1) st.x++;			// BOARD_MAP_Y�� -1 ������ ���������� ������ ���ǹ�
				break;
			case SPACE: if (maps[st.y][st.x] == 0)					// �ش� ��ġ ���� 0�̶�� SPACE�� �Է����� �÷��̾��� �� �Է�, ���� ��ģ�ٸ� �Է��� �ȵǵ��� ó��
			{
				gotoxy(st.x * 2, st.y);
				
				if (turn == BLACK_S)		// �浹 ��
				{
					maps[st.y][st.x] = BLACK_S;		// �浹 ������ ��ǥ, maps�� �迭�� ��ġ ��(�浹 1, �鵹 2�� ��)�� �÷��̾��� �� ���� �°� ���� �� ����
					playingTaksound();
					printf("��");
					check(st, maps, turn);			// ���� 5�� ���Ҵ���, ��ġ���� �˻�
					turn = WHITE_S;					// �¸� ������ �ƴϰ� �������� ���� ���Ҵٸ� �鵹�� �� �ѱ�
				}
				else                         // �鵹 ��
				{
					maps[st.y][st.x] = WHITE_S;		// �鵹 ������ ��ǥ, maps�� �迭�� ��ġ ��(�浹 1, �鵹 2�� ��)�� �÷��̾��� �� ���� �°� ���� �� ����
					playingTaksound();
					printf("��");
					check(st, maps, turn);			// ���� 5�� ���Ҵ���, ��ġ���� �˻�
					turn = BLACK_S;					// �¸� ������ �ƴϰ� �������� ���� ���Ҵٸ� �浹�� �� �ѱ�
				}
			}
				break;
			case ESC: exit(0);						// ESCŰ�� ������ �ܼ�â ����
						break;
			case q:
				return;
			}
			gotoxy(st.x * 2, st.y);					// ������ �� ������ ������ �̵��ϰ� ��Ȯ�� ������ ���� st.x�� 2�� �����ش�.
		}											// ���� ������ 2�� �Ѵٸ� ��Ȯ�� ��ǥ�� Ŀ���� �̵����� �ʰ� ��߳��� �Ǹ�, ���� ��ġ�� �࿭�� ���� �ʰ� ��߳��� �ȴ�.
	}
}

void ResetGame(int maps[BOARD_MAP_Y][BOARD_MAP_X])				// ���� ����۽� ���� �ٽ� �׸���
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
	system("title ����_ver0.1");					// ���� ����
	system("mode con:cols=57 lines=30");		// col ���� ����, lines ���� ����

	playingbgm();

	int maps[BOARD_MAP_Y][BOARD_MAP_X] = { 0 , };
	
	color(11);
	printf("+------------------------------------------------+\n");
	printf("|                                                |\n");
	printf("|                   ���� ����                    |\n");
	printf("|                                                |\n");
	printf("+------------------------------------------------+\n");

	color(7);
	printf("2���� �÷��̾ ������ ���鼭 �÷��� �մϴ�.\n");
	printf("��뺸�� ���� 5���� ���� �Ϸķ� ������ �¸��մϴ�.\n");
	printf("�����Ϸ��� �ƹ� Ű�� �����ּ���.\n");
	
	_getch();

	system("cls");

	Board();
	SetGame(maps);

	while (1)				// ����� �� ��� �ٽ� �����ǰ� ���� ������ �ҷ���
	{	
		_getch();
		
		system("cls");
		
		Board();
		
		SetGame(maps);
		
		CursorView2();		// �ٽ� Ŀ�� ǥ��
		
		ResetGame(maps);
	}

	return 0;
}