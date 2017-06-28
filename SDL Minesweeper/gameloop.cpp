#include "functions.h"
#include "gameScene.h"

bool gameloop(Window *win, int level)
{
	gameScene scene(win,level);

	while (true)
	{

		scene.event();

		scene.update();

		if (scene.isOver())
			break;

		scene.rend();
	}

	return scene.isEscape();
}