#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//定义正方形棋盘格点个数
#define  MAX 30
#define LENGTH 5
//定义方向键的键值数字
#define LEFT 0x4b
#define RIGHT 0x4d
#define UP 0x48
#define DOWN 0x50



int ci=MAX/2, cj=MAX/2;//初始蛇头位置
int addlength = LENGTH;//初始长度
int direction = RIGHT;//初始方向
int lifetime[MAX][MAX] = { 0 };//生存时间数组
int luckytable[MAX][MAX] = { 0 };

//产生幸运果实
void creatluckyapple()
{
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
			luckytable[i][j] = 0;
	}
	int x, y;
	//产生随机种子 
	do
	{
		srand(time(NULL));
		x = (int)(MAX*rand() / (RAND_MAX + 1.0));
		y = (int)(MAX*rand() / (RAND_MAX + 1.0));
	} while (lifetime[x][y] != 0);
		luckytable[x][y] = 1;
}
 

//初始化
void initialization(void)
{
	for (int i = 0; i < LENGTH; i++)lifetime[MAX / 2][MAX / 2 - i] = LENGTH - i;
}

//定义函数,返回每一个格点将要输出的图形是两个空格还是黑色格子
char* getstyle(int i, int j)
{
	if (luckytable[i][j] == 1)
	{
		return "■";
	}
	else
	{
		if (lifetime[i][j] > 0)
			return "■";
		else
			return "  ";
	}
}


void display(void)
{
	//还有边框
	for (int i = 1; i <= MAX + 2; i++)printf("▓");
	printf("\n");
	for (int i = 0; i < MAX; i++)
	{
		printf("▓");
		for (int j = 0; j < MAX; j++)printf(getstyle(i, j));
		printf("▓\n");
	}
	for (int i = 1; i <= MAX + 2; i++)printf("▓");
	printf("\n");
}

void lesslifetime(void)
{
	for (int i = 0; i < MAX;i++)
	{
		for (int j = 0; j < MAX; j++)
			if (lifetime[i][j] > 0)lifetime[i][j]--;
	}
}

void nextpoint(int direction)
{
	switch (direction)
	{
	case UP:ci--; break;
	case DOWN:ci++; break;
	case LEFT:cj--; break;
	case RIGHT:cj++;
	}
}

int ifgameover(void)
{
	if (ci < 0 || ci >= MAX || cj < 0 || cj >= MAX)return 1;
	if (lifetime[ci][cj] != 0)return 1;
	return 0;
}

int finddirection(void)
{
	
	if (_kbhit())
	{
		int input = _getch();
		if (input == 0xe0)
		{
			 return  direction=_getch();
		}
		else if (input == 27)
		{
			exit(0);
		}
	}
	return direction;
}


int main(void)
{
	system("title 贪吃蛇 by王志红");
	system("mode con cols=65 lines=34");
	
	initialization();
	creatluckyapple();
	display();
	while (1)
	{
		system("cls");
		finddirection();
		nextpoint(direction);
		
		if (ifgameover())
		{
			system("cls");
			printf("GameOver!\n");
			system("pause");
			break;
		}
		if (luckytable[ci][cj] == 1)
		{
			lifetime[ci][cj] += addlength++; creatluckyapple();
		}
		else 
		{
			lesslifetime();
			lifetime[ci][cj] += addlength;
			
		}		
		display();
		Sleep(500);		
	}
}
