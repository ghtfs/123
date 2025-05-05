#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//自定义棋盘大小
#define ROW 3
#define COL 3
//二维数组初始化
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
//打印棋盘
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
//玩家回合
void PlayerTurn(char board[ROW][COL], int row, int col)
{
	while (1)
	{
		printf("请玩家输入落子坐标\n");
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
		printf("输入错误，请重新输入\n\n");
	}
	DisplayBoard(board, ROW, COL);
}
//电脑回合
void ComputerTurn(char board[ROW][COL], int row, int col)
{
	srand((unsigned)time(NULL));
	printf("电脑落子\n");
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
//平局判定
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
//游戏状态
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
//游戏菜单
void menu()
{
	printf("      三 子 棋      \n");
	printf("####################\n");
	printf("#    1.开始游戏    #\n");
	printf("#    0.退出游戏    #\n");
	printf("####################\n\n");
}
//游戏函数本体
void game()
{
	//创建二维数组
	char board[ROW][COL];
	//初始化棋盘
	InitBoard(board, ROW, COL);
	//打印棋盘
	DisplayBoard(board, ROW, COL);
	printf("注意，横纵坐标范围均为1到%d，横纵坐标用空格隔开\n\n", ROW);
	int state = 0;
	int firstPlayer;
	printf("请选择先手（1. 玩家先手 2. 电脑先手）：");
	scanf("%d", &firstPlayer);
	if (firstPlayer == 2)
		goto begin;
	while (1)
	{
	//玩家走
	PlayerTurn(board, ROW, COL);
	// 判断输赢
	state = GameState(board, ROW, COL);
	if (state != 'C')
		break;
	begin:
	// 电脑走
	ComputerTurn(board, ROW, COL);
	// 判断输赢
	state = GameState(board, ROW, COL);
	if (state != 'C')
		break;
	}
	//结算
	if (state == 'O')
		printf("玩家获胜\n\n");
	else if (state == 'X')
		printf("电脑获胜\n\n");
	else
		printf("平局\n\n");
}

int main()
{
	int input = 1;
	while (input)
	{
		menu();
		printf("请选择\n");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("开始游戏\n");
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("输入错误，重新输入\n\n");
			break;
		}
	}
	return 0;
}