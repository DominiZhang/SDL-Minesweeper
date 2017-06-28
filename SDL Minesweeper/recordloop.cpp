#include "functions.h"
#include "recordScene.h"

bool recordloop(Window *win)
{
	recordScene scene(win);

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