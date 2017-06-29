//=============================
//程序名称：SDL Minesweeper
//版本号：1.0
//制作人：杨新瑞
//				
//
//创建时间：2017-6-27 08:54:58
//完工时间：2017-6-29 08:51:50
//代码量：1459行
//制作周期：3 天
//	
//
//=============================

#include "functions.h"

int main(int argc, char **argv)
{
	Window *window = new Window;
	window->Init(u8"SDL Minesweeper", Win_L, Win_H);//添加u8以支持中文

	mainloop(window);
	
	window->Quit();
	delete window;
	
	return 0;
}