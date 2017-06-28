#pragma once
#include "functions.h"

class gameScene
{
	enum State
	{
		Gaming,
		Win,
		Lose
	};

	int direct[8][2] = { { 0,-1 },{ 1,-1 },{ 1,0 },{ 1,1 },{ 0,1 },{ -1,1 },{ -1,0 },{ -1,-1 } };

public:
	gameScene(Window *win, int level);
	~gameScene();

	void event();
	void update();
	void rend();
	bool isOver();
	bool isEscape();

private:
	void mouseEvent();
	void keyEvent();

	void init();
	void setBomb();
	void exploreBomb(int &num,int x,int y);
	void setNum();

	void digBomb(int x,int y);
	void surchNum(int x,int y, int deep);

	void update_time();
	void update_flag();

	bool isWin();

	void rend_background();
	void rend_map();
	void rend_loading();
	void rend_cursor();

private:
	Window *win;
	SDL_Event events;
	State state;

	int level;
	int time;
	int time_mm;
	int bomb;
	int flag;

	int mapx;
	int mapy;
	int mapw;
	int maph;
	int map[30][16][2];

	bool isclick;
	bool isover;
	bool isescape;
};

