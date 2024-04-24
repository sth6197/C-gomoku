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

#define BOARD_MAP_X 20		// ������ ����
#define BOARD_MAP_Y 20		// ������ ����
#define BLACK_S 1			// �浹
#define WHITE_S 2			// �鵹

typedef struct              // ��ǥ
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
	COORD pos = { x - 1, y - 1 };
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

void Board()			// ������ �Լ�
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
	printf("���۹� : Ű���� ����Ű - �̵�, �����̽��� - ������\n");
	printf("�ٽ� ����: Q\n\n");
	printf("���� ���� :  ESC\n");
	printf("���� �� ó�� ������ �ٽ� �������� ��� Q�� �� �� �̻� �����ּ���.\n");
}

int search(xy st, int maps[BOARD_MAP_Y][BOARD_MAP_X], int flag, int u, int ud)		// ��, �Ʒ�, ��, ��, �밢�� ����
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

void check(xy st, int maps[BOARD_MAP_Y][BOARD_MAP_X], int turn)		// ���� ����
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
				printf("�浹 �¸�!");
			}
			else
			{
				printf("�鵹 �¸�!");
			}
			CursorView();	// ���� ���� ���� �� Ŀ�� ����
			
			//Sleep(3000);
		}
	}
}

void SetGame(int maps[BOARD_MAP_Y][BOARD_MAP_X])		// Ű����, �÷��̾� �� �Լ�
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

				if (turn == BLACK_S)		// �浹 ��
				{
					maps[st.y][st.x] = BLACK_S;
					printf("��");
					check(st, maps, turn);
					turn = WHITE_S;
				}
				else                         // �鵹 ��
				{
					maps[st.y][st.x] = WHITE_S;
					printf("��");
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

//	void Restartquestion()
//	{
//		color(14);
//		printf("������ �ٽ� �����Ͻ÷��� Q�� �����ּ���.\n");
//		
//		_getch();
//	}


int main()
{
	system("title ����");
	system("mode con:cols=55 lines=30");		// col ����, lines ����

	int maps[BOARD_MAP_Y][BOARD_MAP_X] = { 0 , };
	
	color(9);
	printf("+------------------------------------------------+\n");
	printf("|                                                |\n");
	printf("|                 ���� ����                      |\n");
	printf("|                                                |\n");
	printf("+------------------------------------------------+\n");

	printf("2���� �÷��̾ ������ ���鼭 �÷��� �մϴ�.\n");
	printf("��뺸�� ���� 5���� ���� �Ϸķ� ������ �¸��մϴ�.\n");
	printf("�����Ϸ��� �ƹ� Ű�� �����ּ���.\n");
	
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
		
		CursorView2();	// �ٽ� Ŀ�� ǥ��
		
		ResetGame(maps);
	}

	return 0;
}