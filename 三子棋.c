#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//�Զ������̴�С
#define ROW 3
#define COL 3
//��ά�����ʼ��
void InitBoard(char arr[ROW][COL], int row, int col)
{
	int i = 0, j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			arr[i][j] = ' ';
		}
	}
}
//��ӡ����
void DisplayBoard(char board[ROW][COL], int row, int col)
{
	int i = 0, j = 0;
	for (i = 0; i < row; i++)
	{
		if (i == 0)
		{
			for (j = 0; j < col; j++)
			{

				printf("+---", board[i][j]);
			}
			printf("+\n");
		}
		for (j = 0; j < col; j++)
		{
			printf("| %c ", board[i][j]);
		}
		printf("|\n");
		for (j = 0; j < col; j++)
		{
			if (i < row - 1)
				printf("+---");
			else
				printf("+---", board[i][j]);
		}
		printf("+\n");
	}
}
//��һغ�
void PlayerTurn(char board[ROW][COL], int row, int col)
{
	while (1)
	{
		printf("�����������������\n");
		int x, y;
		while (getchar() != '\n');
		scanf("%d %d", &x, &y);
		if (x > 0 && x <= row && y > 0 && y <= col)
		{
			if (board[x - 1][y - 1] == ' ')
			{
				board[x - 1][y - 1] = 'O';
				break;
			}
		}
		printf("�����������������\n\n");
	}
	DisplayBoard(board, ROW, COL);
}
//���Իغ�
void ComputerTurn(char board[ROW][COL], int row, int col)
{
	srand((unsigned)time(NULL));
	printf("��������\n");
	while (1)
	{
		int x = rand() % 3;
		int	y = rand() % 3;
		if (x >= 0 && x < row && y >= 0 && y < col)
		{
			if (board[x][y] == ' ')
			{
				board[x][y] = 'X';
				break;
			}
		}
	}
	DisplayBoard(board, ROW, COL);
}
//ƽ���ж�
char Full(char board[ROW][COL], int row, int col)
{
	int i = 0, j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
				return 'C';
		}
	}
	return 'F';
}
//��Ϸ״̬
char GameState(char board[ROW][COL], int row, int col)
{
	int i = 0;
	for (i = 0; i < row; i++)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1] != ' ')
		{
			return board[i][0];
		}
	}
	for (i = 0; i < col; i++)
	{
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[1][i] != ' ')
		{
			return board[0][i];
		}
	}
	if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] || board[2][0] == board[1][1] && board[1][1] == board[0][2]) && board[1][1] != ' ')
	{
		return board[1][1];
	}
	char state = Full(board, row, col);
	return state;
}
//��Ϸ�˵�
void menu()
{
	printf("      �� �� ��      \n");
	printf("####################\n");
	printf("#    1.��ʼ��Ϸ    #\n");
	printf("#    0.�˳���Ϸ    #\n");
	printf("####################\n\n");
}
//��Ϸ��������
void game()
{
	//������ά����
	char board[ROW][COL];
	//��ʼ������
	InitBoard(board, ROW, COL);
	//��ӡ����
	DisplayBoard(board, ROW, COL);
	printf("ע�⣬�������귶Χ��Ϊ1��%d�����������ÿո����\n\n", ROW);
	int state = 0;
	int firstPlayer;
	printf("��ѡ�����֣�1. ������� 2. �������֣���");
	scanf("%d", &firstPlayer);
	if (firstPlayer == 2)
		goto begin;
	while (1)
	{
	//�����
	PlayerTurn(board, ROW, COL);
	// �ж���Ӯ
	state = GameState(board, ROW, COL);
	if (state != 'C')
		break;
	begin:
	// ������
	ComputerTurn(board, ROW, COL);
	// �ж���Ӯ
	state = GameState(board, ROW, COL);
	if (state != 'C')
		break;
	}
	//����
	if (state == 'O')
		printf("��һ�ʤ\n\n");
	else if (state == 'X')
		printf("���Ի�ʤ\n\n");
	else
		printf("ƽ��\n\n");
}

int main()
{
	int input = 1;
	while (input)
	{
		menu();
		printf("��ѡ��\n");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("��ʼ��Ϸ\n");
			game();
			break;
		case 0:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("���������������\n\n");
			break;
		}
	}
	return 0;
}