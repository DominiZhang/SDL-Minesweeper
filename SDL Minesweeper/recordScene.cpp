#include "recordScene.h"



recordScene::recordScene(Window *win):win(win)
{
	easy = readHiScore(1);
	medium = readHiScore(2);
	expert = readHiScore(3);

	isover = false;
	isescape = false;
}


recordScene::~recordScene()
{
}

void recordScene::event()
{
	while (SDL_PollEvent(&events))
	{
		//If user closes the window
		if (events.type == SDL_QUIT)
		{
			isover = true;
			isescape = true;
			return;
		}

		if (events.type == SDL_MOUSEBUTTONDOWN)
		{
			mouseEvent();
		}

		if (events.type == SDL_KEYDOWN)
		{
			keyEvent();
		}
	}
}

void recordScene::update()
{
}

void recordScene::rend()
{
	win->Clear();

	rend_background();
	rend_record();
	
	win->Present();
}

bool recordScene::isOver()
{
	return isover;
}

bool recordScene::isEscape()
{
	return isescape;;
}

void recordScene::mouseEvent()
{
	isover = true;
}

void recordScene::keyEvent()
{
	isover = true;
}

void recordScene::rend_background()
{
	boxRGBA(win->getRenderer(), 0, 0, Win_L, Win_H, 18, 103, 72, 255);

	win->RenderText("Highest Records", Font_kaiti, 40, 100, 40, SDL_Color{ 255,255,255 });

	win->RenderText("Easy", Font_kaiti, 100, 200, 30, SDL_Color{ 104,171,40 });

	boxRGBA(win->getRenderer(), 100, 260, Win_L-100, 265, 255, 255, 255, 255);

	win->RenderText("Medium", Font_kaiti, 100, 300, 30, SDL_Color{ 211,174,9 });

	boxRGBA(win->getRenderer(), 100, 360, Win_L - 100, 365, 255, 255, 255, 255);

	win->RenderText("Expert", Font_kaiti, 100, 400, 30, SDL_Color{ 215,98,48 });

	win->RenderText("Press any key to return", Font_kaiti, 250, 450, 25, SDL_Color{ 255,255,255 });
}

void recordScene::rend_record()
{
	char buffer[255];

	if(easy>=10000)
		win->RenderText("No Record", Font_kaiti, 300, 200, 30, SDL_Color{ 104,171,40 });
	else
	{
		sprintf(buffer, "%3d:%2d", easy / 60, easy % 60);
		win->RenderText(buffer, Font_kaiti, 300, 200, 30, SDL_Color{ 104,171,40 });
		if(easy % 60<10)
			win->RenderText("0", Font_kaiti, 360, 200, 30, SDL_Color{ 104,171,40 });
		if (easy / 60<10)
			win->RenderText("0", Font_kaiti, 315, 200, 30, SDL_Color{ 104,171,40 });
	}
	
	if (medium >= 10000)
		win->RenderText("No Record", Font_kaiti, 300, 300, 30, SDL_Color{ 211,174,9 });
	else
	{
		sprintf(buffer, "%3d:%2d", medium / 60, medium % 60);
		win->RenderText(buffer, Font_kaiti, 300, 300, 30, SDL_Color{ 211,174,9 });
		if (medium % 60<10)
			win->RenderText("0", Font_kaiti, 360, 300, 30, SDL_Color{ 211,174,9 });
		if (medium / 60<10)
			win->RenderText("0", Font_kaiti, 315, 300, 30, SDL_Color{ 211,174,9 });
	}

	if (expert >= 10000)
		win->RenderText("No Record", Font_kaiti, 300, 400, 30, SDL_Color{ 215,98,48 });
	else
	{
		sprintf(buffer, "%3d:%2d", expert / 60, expert % 60);
		win->RenderText(buffer, Font_kaiti, 300, 400, 30, SDL_Color{ 215,98,48 });
		if (expert % 60<10)
			win->RenderText("0", Font_kaiti, 360, 400, 30, SDL_Color{ 215,98,48 });
		if (expert / 60<10)
			win->RenderText("0", Font_kaiti, 315, 400, 30, SDL_Color{ 215,98,48 });
	}
}
