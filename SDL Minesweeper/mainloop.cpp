#include "functions.h"
#include "menuScene.h"

bool mainloop(Window *win)
{
	menuScene scene(win);

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