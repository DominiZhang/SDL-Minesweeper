#pragma once
#include "functions.h"

class menuScene
{
public:
	menuScene(Window *win);
	~menuScene();

	void event();
	void update();
	void rend();
	bool isOver();
	bool isEscape();

private:
	void mouseEvent();
	void keyEvent();

	void rend_background();
	void rend_button();
	void rend_buttoneffect();
	void rend_OpenAD();

private:
	Window *win;
	SDL_Event events;

	bool isover;
	bool isescape;
};

