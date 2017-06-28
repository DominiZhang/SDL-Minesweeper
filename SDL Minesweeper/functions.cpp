#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void saveHiScore(int time, int level)
{
	FILE *fp;
	char buffer[255];
	sprintf(buffer,"data/Save/time%d.txt",level);
	fp = fopen(buffer, "w");	//��д�ķ�ʽ���ļ�
	if (fp)	//�򿪳ɹ�
	{
		fprintf(fp, "%d",time);	//����߷���д���ļ�
		fclose(fp);	//�ر��ļ�
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
	fp = fopen(buffer, "r");	//�Զ��ķ�ʽ���ļ�
	if (fp)	//�򿪳ɹ�
	{
		fscanf(fp, "%d", &time);	//����߷������ļ��ж���
		fclose(fp);	//�ر��ļ�
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
	srand((unsigned)time(NULL));//ѡȡ�����ļ�
	do
	{
		num = (int)rand() % max;
	} while (num < min || num > max);

	return num;
}
