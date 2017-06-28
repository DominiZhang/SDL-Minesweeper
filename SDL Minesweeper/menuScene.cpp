#include "menuScene.h"


menuScene::menuScene(Window * win):win(win)
{
	isover = false;
	isescape = false;
	rend_OpenAD();
	SDL_Delay(2500);
}

menuScene::~menuScene()
{
}

void menuScene::event()
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

void menuScene::update()
{
}

void menuScene::rend()
{
	win->Clear();

	rend_background();
	rend_buttoneffect();
	rend_button();

	win->Present();
}

bool menuScene::isOver()
{
	return isover;
}

bool menuScene::isEscape()
{
	return isescape;
}

void menuScene::mouseEvent()
{
	int x, y;
	x = events.motion.x;
	y = events.motion.y;

	if (events.button.button == SDL_BUTTON_LEFT)
	{
		if((x>40&&x<40+250)&&(y>170&&y<170+50))
		{
			if(gameloop(win, 1))
			{
				isover = true;
				isescape = true;
			}
		}
		else if ((x>40 && x<40 + 250) && (y>230 && y<230 + 50))
		{
			if (gameloop(win, 2))
			{
				isover = true;
				isescape = true;
			}
		}
		else if ((x>40 && x<40 + 250) && (y>290 && y<290 + 50))
		{
			if (gameloop(win, 3))
			{
				isover = true;
				isescape = true;
			}
		}
		else if ((x>40 && x<40 + 250) && (y>350 && y<350 + 50))
		{
			if (recordloop(win))
			{
				isover = true;
				isescape = true;
			}
		}
		else if ((x>40 && x<40 + 250) && (y>410 && y<410 + 50))
		{
			isover = true;
			isescape = true;
		}
	}
}

void menuScene::keyEvent()
{
	switch (events.key.keysym.sym)
	{
	case SDLK_ESCAPE:
		isover = true;
		isescape = true;
		break;
	}
}

void menuScene::rend_background()
{
	boxRGBA(win->getRenderer(), 0, 0, Win_L, Win_H, 18, 103, 72, 255);

	win->RenderText("SDL Minesweeper", Font_kaiti, 40, 100, 40, SDL_Color{ 255,255,255 });
}

void menuScene::rend_button()
{
	win->Draw(win->mPicture->easy, 40, 170);
	win->Draw(win->mPicture->medium, 40, 230);
	win->Draw(win->mPicture->expert, 40, 290);
	win->Draw(win->mPicture->highest, 40, 350);
	win->Draw(win->mPicture->escape, 40, 410);
}

void menuScene::rend_buttoneffect()
{
	if (events.type == SDL_MOUSEMOTION)
	{
		if ((events.motion.x>40 && events.motion.x<40 + 250) && (events.motion.y>170 && events.motion.y<170 + 50))
		{
			boxRGBA(win->getRenderer(), 40-2, 170-2,40+250+2, 170+50+2,0, 122, 204, 255);
		}
		else if ((events.motion.x>40 && events.motion.x<40 + 250) && (events.motion.y>230 && events.motion.y<230 + 50))
		{
			boxRGBA(win->getRenderer(), 40 - 2, 230 - 2, 40 + 250 + 2, 230 + 50 + 2, 0, 122, 204, 255);
		}
		else if ((events.motion.x>40 && events.motion.x<40 + 250) && (events.motion.y>290 && events.motion.y<290 + 50))
		{
			boxRGBA(win->getRenderer(), 40 - 2, 290 - 2, 40 + 250 + 2, 290 + 50 + 2, 0, 122, 204, 255);
		}
		else if ((events.motion.x>40 && events.motion.x<40 + 250) && (events.motion.y>350 && events.motion.y<350 + 50))
		{
			boxRGBA(win->getRenderer(), 40 - 2, 350 - 2, 40 + 250 + 2, 350 + 50 + 2, 0, 122, 204, 255);
		}
		else if ((events.motion.x>40 && events.motion.x<40 + 250) && (events.motion.y>410 && events.motion.y<410 + 50))
		{
			boxRGBA(win->getRenderer(), 40 - 2, 410 - 2, 40 + 250 + 2, 410 + 50 + 2, 0, 122, 204, 255);
		}
	}
}

void menuScene::rend_OpenAD()
{
	win->Clear();

	win->Draw(win->mPicture->OpenAD, 0, 0);

	win->Present();
}
