//=============================
//程序名称：SDL Minesweeper
//版本号：1.0
//制作团队：实训五组：
//				组长：杨新瑞
//				组员：余德川，浦虹汕，汪婷婷，康瑞，高衫，李阳
//
//创建时间：2017-6-27 08:54:58
//完工时间：
//代码量：行
//制作周期：2 天
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