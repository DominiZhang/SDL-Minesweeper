//=============================
//�������ƣ�SDL Minesweeper
//�汾�ţ�1.0
//�����Ŷӣ�ʵѵ���飺
//				�鳤��������
//				��Ա����´����ֺ��ǣ������ã����𣬸���������
//
//����ʱ�䣺2017-6-27 08:54:58
//�깤ʱ�䣺
//����������
//�������ڣ�2 ��
//	
//
//=============================

#include "functions.h"

int main(int argc, char **argv)
{
	Window *window = new Window;
	window->Init(u8"SDL Minesweeper", Win_L, Win_H);//���u8��֧������

	mainloop(window);
	
	window->Quit();
	delete window;
	
	return 0;
}