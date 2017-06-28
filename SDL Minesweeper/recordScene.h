#pragma once
#include "functions.h"

class recordScene
{
public:
	recordScene(Window *win);
	~recordScene();

	void event();
	void update();
	void rend();
	bool isOver();
	bool isEscape();

private:
	void mouseEvent();
	void keyEvent();

	void rend_background();
	void rend_record();

private:
	Window *win;
	SDL_Event events;

	int easy;
	int medium;
	int expert;

	bool isover;
	bool isescape;
};

