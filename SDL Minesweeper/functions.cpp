#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void saveHiScore(int time, int level)
{
	FILE *fp;
	char buffer[255];
	sprintf(buffer,"data/Save/time%d.txt",level);
	fp = fopen(buffer, "w");	//以写的方式打开文件
	if (fp)	//打开成功
	{
		fprintf(fp, "%d",time);	//将最高分数写入文件
		fclose(fp);	//关闭文件
	}
	else
		throw std::runtime_error("Score Write Failed");
}

int readHiScore(int level)
{
	FILE *fp;
	int time = 0;
	char buffer[255];
	sprintf(buffer, "data/Save/time%d.txt", level);
	fp = fopen(buffer, "r");	//以读的方式打开文件
	if (fp)	//打开成功
	{
		fscanf(fp, "%d", &time);	//将最高分数从文件中读出
		fclose(fp);	//关闭文件
	}
	else
		throw std::runtime_error("Score Read Failed");
	return time;
}

int Myrand(int max,int min)
{
	if (max < min)
		throw std::runtime_error("Myrand max<min");
	if(max==0)
		throw std::runtime_error("Myrand max==0");

	int num;
	srand((unsigned)time(NULL));//选取种子文件
	do
	{
		num = (int)rand() % max;
	} while (num < min || num > max);

	return num;
}
