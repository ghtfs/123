#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROW 10
#define COL 10

void menu()
{
	printf("    扫    雷    \n");
	printf("################\n");
	printf("#  1.开始游戏  #\n");
	printf("#  0.退出游戏  #\n");
	printf("################\n\n");
}

void Initialization(char filed[ROW][COL],int row,int col)
{
	int i = 0, j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			filed[i][j] = ' ';
		}
	}
}

int lay_mines(char filed[ROW][COL], int row, int col)
{
	srand((unsigned)time(NULL));
	int N = 0;
	while (N < col)
	{
		N = rand() % 21;
	}
	int m = 0;
	for (m = 0; m < N; m++)
	{
		while (1)
		{
			int i = rand() % row, j = rand() % col;
			if (filed[i][j] == ' ')
			{
				filed[i][j] = '*';
				break;
			}
		}
	}
	return N;
}


void display_filed(char filed[ROW][COL], int row, int col)
{
	int i = 0, j = 0;
	printf(" ");
	for (j = 0; j < col; j++)
	{
		printf("   %d", j + 1);
	}
	printf("\n");
	for (i = 0; i < row; i++)
	{
		
		printf("  ");
		for (j = 0; j < col; j++)
		{
			printf("+---");
		}
		printf("+\n%2d",i+1);
		for (j = 0; j < col; j++)
		{
			printf("| %c ",filed[i][j]);
		}
		printf("|\n");
	}
	printf("  ");
	for (j = 0; j < col; j++)
	{
		printf("+---");
	}
	printf("+\n");
}

int statistics(char filed[ROW][COL],int i,int j)
{
	int x = 0,q=i,e=j;
	for (q = i - 1; q <= i + 1; q++)
	{
		if (q >= 0 && q < ROW)
		{
			for (e = j - 1; e <= j + 1; e++)
			{
				if (e >= 0 && e < COL)
				{
					if (filed[q][e] == '*')
					{
						x += 1;
					}
				}
			}
		}
	}
	return x;
}

void jiesuan(char filed[ROW][COL], char Filed[ROW][COL])
{
	int i = 0, j = 0;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (filed[i][j] != '*' && Filed[i][j] != ' ')
			{
				filed[i][j] = Filed[i][j];
			}
		}
	}
}

int condition(char filed[ROW][COL], char Filed[ROW][COL], int N)
{
	int i = 0, j = 0, qz = 0;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (filed[i][j] == '*' && Filed[i][j] == 'P')
			{
				qz++;
			}
		}
	}
	if (qz == N)
		return 1;
	else
		return 0;
}

void clearance(char filed[ROW][COL],char Filed[ROW][COL], int row, int col,int N)
{
	int n = 0, i = 0, j = 0, k = 0, x = 0;
	int mines = 0;
	printf("输入格式要求：A空格B空格C，A(0为插旗，1为挖开),B为行数，C为列数。全插满棋子也是可以赢的\n");
	for (n = 1;; n++)
	{
		int end = condition(filed, Filed, N);
		if (end)
		{
			printf("游戏胜利！\n");
			printf("总回合数=%d\n",n-1);
			break;
		}
		scanf("%d %d %d",&k, &i, &j );
		while (getchar() != '\n');
		if (k != 0 && k != 1 || i<1 || i>ROW || j<1 || j>COL)
		{
			printf("输入不符合要求，请重新输入\n");
			n -= 1;
		}
		else
		{
			if (k)
			{
				if (filed[i - 1][j - 1] == '*')
				{
					jiesuan(filed, Filed);
					printf("地雷总数=%d  回合数=%d\n", N, n);
					display_filed(filed, ROW, COL);
					printf("恭喜你挖到地雷了，游戏失败！\n\n");
					break;
				}
				else
				{
					x = statistics(filed, i - 1, j - 1);
					Filed[i - 1][j - 1] = x + '0';
					printf("地雷总数=%d  回合数=%d\n", N, n);
					display_filed(Filed, ROW, COL);
					printf("游戏继续\n");

				}
			}
			else
			{
				Filed[i - 1][j - 1] = 'P';
				printf("地雷总数=%d  回合数=%d\n", N, n);
				display_filed(Filed, ROW, COL);
				printf("游戏继续\n");

			}
		}
	}
}

void game()
{
	char filed[ROW][COL];//创建二维数组1
	Initialization(filed, ROW, COL);//初始化雷区
	char Filed[ROW][COL];//创建二维数组2
	Initialization(Filed, ROW, COL);//初始化雷区
	int N = lay_mines(filed, ROW, COL);//埋雷
	display_filed(Filed, ROW, COL);//展示游戏区域
	clearance(filed,Filed, ROW, COL, N);//玩家开始排雷
}

int main()
{
	int g = 1;
	while (g)
	{
		menu();
		printf("请选择\n");
		scanf("%d", &g);
		while (getchar() != '\n');
		if(g<0 ||g>1)
			printf("输入不符合要求，请重新输入\n");
		else
		{
			switch (g)
			{
			case 1:
				game();
				break;
			case 0:
				break;
			default:
				printf("选项不存在，请重新输入\n\n");
				break;
			}
		}
	}
	return 0;
}