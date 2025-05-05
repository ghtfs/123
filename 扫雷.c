#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROW 10
#define COL 10

void menu()
{
	printf("    ɨ    ��    \n");
	printf("################\n");
	printf("#  1.��ʼ��Ϸ  #\n");
	printf("#  0.�˳���Ϸ  #\n");
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
	printf("�����ʽҪ��A�ո�B�ո�C��A(0Ϊ���죬1Ϊ�ڿ�),BΪ������CΪ������ȫ��������Ҳ�ǿ���Ӯ��\n");
	for (n = 1;; n++)
	{
		int end = condition(filed, Filed, N);
		if (end)
		{
			printf("��Ϸʤ����\n");
			printf("�ܻغ���=%d\n",n-1);
			break;
		}
		scanf("%d %d %d",&k, &i, &j );
		while (getchar() != '\n');
		if (k != 0 && k != 1 || i<1 || i>ROW || j<1 || j>COL)
		{
			printf("���벻����Ҫ������������\n");
			n -= 1;
		}
		else
		{
			if (k)
			{
				if (filed[i - 1][j - 1] == '*')
				{
					jiesuan(filed, Filed);
					printf("��������=%d  �غ���=%d\n", N, n);
					display_filed(filed, ROW, COL);
					printf("��ϲ���ڵ������ˣ���Ϸʧ�ܣ�\n\n");
					break;
				}
				else
				{
					x = statistics(filed, i - 1, j - 1);
					Filed[i - 1][j - 1] = x + '0';
					printf("��������=%d  �غ���=%d\n", N, n);
					display_filed(Filed, ROW, COL);
					printf("��Ϸ����\n");

				}
			}
			else
			{
				Filed[i - 1][j - 1] = 'P';
				printf("��������=%d  �غ���=%d\n", N, n);
				display_filed(Filed, ROW, COL);
				printf("��Ϸ����\n");

			}
		}
	}
}

void game()
{
	char filed[ROW][COL];//������ά����1
	Initialization(filed, ROW, COL);//��ʼ������
	char Filed[ROW][COL];//������ά����2
	Initialization(Filed, ROW, COL);//��ʼ������
	int N = lay_mines(filed, ROW, COL);//����
	display_filed(Filed, ROW, COL);//չʾ��Ϸ����
	clearance(filed,Filed, ROW, COL, N);//��ҿ�ʼ����
}

int main()
{
	int g = 1;
	while (g)
	{
		menu();
		printf("��ѡ��\n");
		scanf("%d", &g);
		while (getchar() != '\n');
		if(g<0 ||g>1)
			printf("���벻����Ҫ������������\n");
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
				printf("ѡ����ڣ�����������\n\n");
				break;
			}
		}
	}
	return 0;
}