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
	void foundNum();

	void update_time();
	void update_flag();

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

