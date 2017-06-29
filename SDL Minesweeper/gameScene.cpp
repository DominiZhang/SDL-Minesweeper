#include "gameScene.h"

gameScene::gameScene(Window *win, int level) :win(win)
{
	isover = false;
	isescape = false;

	this->level = level;

	switch (level)
	{
	case 1:
		bomb = 10;
		mapw = 9;
		maph = 9;
		mapx = (Win_L - mapw * 20) / 2;
		mapy = (Win_H - 100 - maph * 20) / 2 + 80;
		break;
	case 2:
		bomb = 40;
		mapw = 16;
		maph = 16;
		mapx = (Win_L - mapw * 20) / 2;
		mapy = (Win_H - 100 - maph * 20) / 2 + 80;
		break;
	case 3:
		bomb = 99;
		mapw = 30;
		maph = 16;
		mapx = (Win_L - mapw * 20) / 2;
		mapy = (Win_H - 100 - maph * 20) / 2 + 80;
		break;
	}

	init();
}


gameScene::~gameScene()
{
}

void gameScene::event()
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

void gameScene::update()
{
	switch (state)
	{
	case Esc:
	case Gaming:
		if (isclick)
		{
			update_time();
			update_flag();
			if (isWin())
				state = Win;
		}
		break;
	case Win:
		update_win();
		break;
	case Lose:
		update_lose();
		break;
	default:
		break;
	}
}

void gameScene::rend()
{
	win->Clear();

	rend_background();
	rend_map();

	switch (state)
	{
	case Gaming:
		if (count > 0)
		{
			rend_loading();
			count--;
		}
		else
		{
			rend_cursor();
		}
		break;
	case Win:
		rend_win();
		break;
	case Lose:
		rend_lose();
		break;
	case Esc:
		rend_esc();
		break;
	}

	rend_buttoneffect();
	rend_button();

	win->Present();
}

bool gameScene::isOver()
{
	return isover;
}

bool gameScene::isEscape()
{
	return isescape;
}

void gameScene::mouseEvent()
{
	int x, y;
	x = events.motion.x;
	y = events.motion.y;

	if (events.button.button == SDL_BUTTON_LEFT)
	{
		switch (state)
		{
		case Gaming:
			if ((x >= mapx&&x <= mapx + mapw * 20) && (y >= mapy&&y <= mapy + maph * 20))
			{
				if (!isclick)
					isclick = true;
				if (issetbomb)
				{
					setBomb();
					setNum();
					issetbomb = false;
				}
				digBomb((x - mapx) / 20, (y - mapy) / 20);
			}
			break;
		case Win:
			if ((x > 100 && x < 100 + 250) && (y > Win_H - 100 && y < Win_H - 100 + 50))
			{
				saveTime();
				isover = true;
			}
			else if ((x > Win_L - 100 - 250 && x < Win_L - 100) && (y > Win_H - 100 && y < Win_H - 100 + 50))
			{
				saveTime();
				init();
			}
			break;
		case Lose:
			if ((x > 100 && x < 100 + 250) && (y > Win_H - 100 && y < Win_H - 100 + 50))
			{
				isover = true;
			}
			else if ((x > Win_L - 100 - 250 && x < Win_L - 100) && (y > Win_H - 100 && y < Win_H - 100 + 50))
			{
				init();
			}
			break;
		case Esc:
			if ((x > 100 && x < 100 + 250) && (y > Win_H - 100 && y < Win_H - 100 + 50))
			{
				isover = true;
			}
			else if ((x > Win_L - 100 - 250 && x < Win_L - 100) && (y > Win_H - 100 && y < Win_H - 100 + 50))
			{
				state = Gaming;
			}
			break;
		}
	}

	if (events.button.button == SDL_BUTTON_RIGHT)
	{
		switch (state)
		{
		case Gaming:
			if ((x >= mapx&&x <= mapx + mapw * 20) && (y >= mapy&&y <= mapy + maph * 20))
			{
				if (map[(x - mapx) / 20][(y - mapy) / 20][1] >= 0)
				{
					map[(x - mapx) / 20][(y - mapy) / 20][1]++;
					if (map[(x - mapx) / 20][(y - mapy) / 20][1] >= 3)
						map[(x - mapx) / 20][(y - mapy) / 20][1] = 0;
				}
			}
			break;
		case Win:

			break;
		case Lose:

			break;
		}
	}
}

void gameScene::keyEvent()
{
	switch (events.key.keysym.sym)
	{
	case SDLK_ESCAPE:
		switch (state)
		{
		case gameScene::Gaming:
			state = Esc;
			break;
		case gameScene::Win:
			saveTime();
			isover = true;
			break;
		case gameScene::Lose:
			isover = true;
			break;
		case gameScene::Esc:
			state = Gaming;
			break;
		default:
			break;
		}
		break;
	}
}

void gameScene::init()
{
	isclick = false;
	issetbomb = true;
	time = 0;
	time_mm = 0;
	flag = bomb;
	count = 30;

	state = Gaming;

	for (int i = 0; i < mapw; i++)
		for (int j = 0; j < maph; j++)
		{
			map[i][j][0] = 0;
			map[i][j][1] = 0;
		}
}

void gameScene::setBomb()
{
	int i = bomb;
	int x, y;
	int mx, my;
	mx = (events.motion.x - mapx) / 20;
	my = (events.motion.y - mapy) / 20;
	while (i)
	{
		x = Myrand(mapw, 0) % mapw;
		y = Myrand(maph, 0) % maph;
		if (map[x][y][0] != 9 && (x != mx&&y != my))
		{
			map[x][y][0] = 9;
			i--;
		}
	}
}

void gameScene::setNum()
{
	int count;

	for (int i = 0; i < mapw; i++)
		for (int j = 0; j < maph; j++)
		{
			if (map[i][j][0] != 9)
			{
				count = 0;
				for (int k = 0; k < 8; k++)
				{
					if ((i + direct[k][0] >= 0 && i + direct[k][0] < mapw) && (j + direct[k][1] >= 0 && j + direct[k][1] < maph))
						if (map[i + direct[k][0]][j + direct[k][1]][0] == 9)
							count++;
				}
				map[i][j][0] = count;
			}
		}
}

void gameScene::saveTime()
{
	if (time < readHiScore(level) || readHiScore(level) >= 10000)
		saveHiScore(time, level);
}

void gameScene::digBomb(int x, int y)
{
	if (map[x][y][1] == 0 || map[x][y][1] == 2)
	{
		map[x][y][1] = -1;
		if (map[x][y][0] == 9)
		{
			state = Lose;
		}
		else if (map[x][y][0] == 0)
		{
			surchNum(x, y, 1);
		}
		else
		{
			surchNum(x, y, 0);
		}
	}
}

void gameScene::surchNum(int x, int y, int deep)
{
	for (int k = 0; k < 8; k++)
		if ((x + direct[k][0] >= 0 && x + direct[k][0] < mapw) && (y + direct[k][1] >= 0 && y + direct[k][1] < maph))
		{
			if (map[x + direct[k][0]][y + direct[k][1]][1] == 0 || map[x + direct[k][0]][y + direct[k][1]][1] == 2)
			{
				if (map[x + direct[k][0]][y + direct[k][1]][0] > 0 && map[x + direct[k][0]][y + direct[k][1]][0] < 9 && map[x + direct[k][0]][y + direct[k][1]][1] != 1)
				{
					if (deep)
						map[x + direct[k][0]][y + direct[k][1]][1] = -1;
				}
				else if (map[x + direct[k][0]][y + direct[k][1]][0] == 0 && map[x + direct[k][0]][y + direct[k][1]][1] != 1)
				{
					map[x + direct[k][0]][y + direct[k][1]][1] = -1;
					surchNum(x + direct[k][0], y + direct[k][1], deep++);
				}
			}
		}
}

void gameScene::update_time()
{
	time_mm++;
	if (time_mm == 60)
	{
		time++;
		time_mm = 0;
	}
}

void gameScene::update_flag()
{
	flag = bomb;
	for (int i = 0; i < mapw; i++)
		for (int j = 0; j < maph; j++)
			if (map[i][j][1] == 1)
				flag--;

}

void gameScene::update_win()
{
	if (count < 1000000)
	{
		if (count / 3 < mapw)
		{
			for (int i = 0; i < maph; i++)
			{
				map[count / 3][i][1] = -1;
			}
		}
		count++;
	}
}

void gameScene::update_lose()
{
	if (count < 1000000)
	{
		if (count / 3 < mapw)
		{
			for (int i = 0; i < maph; i++)
			{
				map[count / 3][i][1] = -1;
			}
		}
		count++;
	}
}

bool gameScene::isWin()
{
	bool iswin = true;

	for (int i = 0; i < mapw; i++)
		for (int j = 0; j < maph; j++)
		{
			if (map[i][j][1] != -1 && map[i][j][0] != 9)
				iswin = false;
		}

	return iswin;
}

void gameScene::rend_background()
{
	char buffer[255];

	win->Draw(win->mPicture->gameBackground, 0, 0);

	win->Draw(win->mPicture->timer_logo, 270, 30);
	win->Draw(win->mPicture->bomb_logo, 420, 30);

	sprintf(buffer, "%3d:%2d", time / 60, time % 60);
	win->RenderText(buffer, Font_kaiti, 320, 40, 30, SDL_Color{ 255,255,255 });
	if (time % 60 < 10)
		win->RenderText("0", Font_kaiti, 380, 40, 30, SDL_Color{ 255,255,255 });
	if (time / 60 < 10)
		win->RenderText("0", Font_kaiti, 335, 40, 30, SDL_Color{ 255,255,255 });

	sprintf(buffer, "%d", flag);
	win->RenderText(buffer, Font_kaiti, 470, 40, 30, SDL_Color{ 255,255,255 });

}

void gameScene::rend_map()
{
	for (int i = 0; i < mapw; i++)
		for (int j = 0; j < maph; j++)
		{
			switch (map[i][j][0])
			{
			case 0:
				win->Draw(win->mPicture->land, mapx + i * 20, mapy + j * 20);
				break;
			case 1:
				win->Draw(win->mPicture->num1, mapx + i * 20, mapy + j * 20);
				break;
			case 2:
				win->Draw(win->mPicture->num2, mapx + i * 20, mapy + j * 20);
				break;
			case 3:
				win->Draw(win->mPicture->num3, mapx + i * 20, mapy + j * 20);
				break;
			case 4:
				win->Draw(win->mPicture->num4, mapx + i * 20, mapy + j * 20);
				break;
			case 5:
				win->Draw(win->mPicture->num5, mapx + i * 20, mapy + j * 20);
				break;
			case 6:
				win->Draw(win->mPicture->num6, mapx + i * 20, mapy + j * 20);
				break;
			case 7:
				win->Draw(win->mPicture->num7, mapx + i * 20, mapy + j * 20);
				break;
			case 8:
				win->Draw(win->mPicture->num8, mapx + i * 20, mapy + j * 20);
				break;
			case 9:
				win->Draw(win->mPicture->bomb, mapx + i * 20, mapy + j * 20);
				break;
			default:
				break;
			}

			switch (map[i][j][1])
			{
			case -1:
				break;
			case 0:
				win->Draw(win->mPicture->grass, mapx + i * 20, mapy + j * 20);
				break;
			case 1:
				win->Draw(win->mPicture->flag, mapx + i * 20, mapy + j * 20);
				break;
			case 2:
				win->Draw(win->mPicture->unknown, mapx + i * 20, mapy + j * 20);
				break;
			default:
				break;
			}
		}

}

void gameScene::rend_loading()
{
	win->Clear();

	win->Draw(win->mPicture->loading, 0, 0);

	win->Present();
}

void gameScene::rend_cursor()
{
	int x, y;
	x = events.motion.x;
	y = events.motion.y;

	if ((x >= mapx&&x <= mapx + mapw * 20) && (y >= mapy&&y <= mapy + maph * 20))
		win->Draw(win->mPicture->cursor, ((x - mapx) / 20) * 20 + mapx - 1, ((y - mapy) / 20) * 20 + mapy - 1);
}

void gameScene::rend_button()
{
	switch (state)
	{
	case gameScene::Gaming:

		break;
	case gameScene::Win:
		if (count / 3 - mapw > 5)
		{
			win->Draw(win->mPicture->menu, 100, Win_H - 100);
			win->Draw(win->mPicture->again, Win_L - 350, Win_H - 100);
		}
		break;
	case gameScene::Lose:
		if (count / 3 - mapw > 5)
		{
			win->Draw(win->mPicture->menu, 100, Win_H - 100);
			win->Draw(win->mPicture->again, Win_L - 350, Win_H - 100);
		}
		break;
	case gameScene::Esc:
		win->Draw(win->mPicture->menu, 100, Win_H - 100);
		win->Draw(win->mPicture->returngame, Win_L - 350, Win_H - 100);
		break;
	default:
		break;
	}
}

void gameScene::rend_buttoneffect()
{
	if (events.type == SDL_MOUSEMOTION)
	{
		switch (state)
		{
		case gameScene::Gaming:

			break;
		case gameScene::Win:
		case gameScene::Lose:
			if (count / 3 - mapw > 5)
			{
				if ((events.motion.x > 100 && events.motion.x < 100 + 250) && (events.motion.y > Win_H - 100 && events.motion.y < Win_H - 100 + 50))
				{
					boxRGBA(win->getRenderer(), 100 - 2, Win_H - 100 - 2, 100 + 250 + 2, Win_H - 100 + 50 + 2, 0, 122, 204, 255);
				}
				else if ((events.motion.x > Win_L - 350 && events.motion.x < Win_L - 350 + 250) && (events.motion.y > Win_H - 100 && events.motion.y < Win_H - 100 + 50))
				{
					boxRGBA(win->getRenderer(), Win_L - 350 - 2, Win_H - 100 - 2, Win_L - 350 + 250 + 2, Win_H - 100 + 50 + 2, 0, 122, 204, 255);
				}
			}
			break;
		case gameScene::Esc:
			if ((events.motion.x > 100 && events.motion.x < 100 + 250) && (events.motion.y > Win_H - 100 && events.motion.y < Win_H - 100 + 50))
			{
				boxRGBA(win->getRenderer(), 100 - 2, Win_H - 100 - 2, 100 + 250 + 2, Win_H - 100 + 50 + 2, 0, 122, 204, 255);
			}
			else if ((events.motion.x > Win_L - 350 && events.motion.x < Win_L - 350 + 250) && (events.motion.y > Win_H - 100 && events.motion.y < Win_H - 100 + 50))
			{
				boxRGBA(win->getRenderer(), Win_L - 350 - 2, Win_H - 100 - 2, Win_L - 350 + 250 + 2, Win_H - 100 + 50 + 2, 0, 122, 204, 255);
			}
			break;
		default:
			break;
		}
	}
}

void gameScene::rend_lose()
{
	if (count / 3 < mapw)
	{
		for (int j = 0; j < maph; j++)
		{
			win->Draw(win->mPicture->effect_goldlight, mapx + (count / 3) * 20, mapy + j * 20);
		}
	}
	else if (count / 3 - mapw >= 0 && count / 3 - mapw <= 5)
	{
		boxRGBA(win->getRenderer(), 0, 0, Win_L, Win_H, 0, 0, 0, (count / 3 - mapw) * 20);
	}
	else
	{
		boxRGBA(win->getRenderer(), 0, 0, Win_L, Win_H, 0, 0, 0, 100);
		win->RenderText("Lose", Font_kaiti, 260, 160, 150, SDL_Color{ 255,255,255 });

	}

}

void gameScene::rend_win()
{
	if (count / 3 < mapw)
	{
		for (int j = 0; j < maph; j++)
		{
			win->Draw(win->mPicture->effect_goldlight, mapx + (count / 3) * 20, mapy + j * 20);
		}
	}
	else if (count / 3 - mapw >= 0 && count / 3 - mapw <= 5)
	{
		boxRGBA(win->getRenderer(), 0, 0, Win_L, Win_H, 0, 0, 0, (count / 3 - mapw) * 20);
	}
	else
	{
		boxRGBA(win->getRenderer(), 0, 0, Win_L, Win_H, 0, 0, 0, 100);


		int record = readHiScore(level);
		char buffer[255];

		if (record >= 10000 || time > record)
		{
			win->RenderText("New Record", Font_kaiti, 150, 120, 100, SDL_Color{ 255,255,255 });
			sprintf(buffer, "%3d:%2d", time / 60, time % 60);
			win->RenderText(buffer, Font_kaiti, 300, 250, 60, SDL_Color{ 255,255,255 });
			if (time % 60 < 10)
				win->RenderText("0", Font_kaiti, 420, 250, 60, SDL_Color{ 255,255,255 });
			if (time / 60 < 10)
				win->RenderText("0", Font_kaiti, 330, 250, 60, SDL_Color{ 255,255,255 });
		}
		else
		{
			win->RenderText("Win", Font_kaiti, 330, 100, 100, SDL_Color{ 255,255,255 });

			win->RenderText("Record", Font_kaiti, 250, 210, 50, SDL_Color{ 255,255,255 });
			sprintf(buffer, "%3d:%2d", time / 60, time % 60);
			win->RenderText(buffer, Font_kaiti, 400, 200, 60, SDL_Color{ 255,255,255 });
			if (time % 60 < 10)
				win->RenderText("0", Font_kaiti, 520, 200, 60, SDL_Color{ 255,255,255 });
			if (time / 60 < 10)
				win->RenderText("0", Font_kaiti, 430, 200, 60, SDL_Color{ 255,255,255 });

			win->RenderText("Final Time", Font_kaiti, 150, 310, 50, SDL_Color{ 255,255,255 });
			sprintf(buffer, "%3d:%2d", time / 60, time % 60);
			win->RenderText(buffer, Font_kaiti, 400, 300, 60, SDL_Color{ 255,255,255 });
			if (time % 60 < 10)
				win->RenderText("0", Font_kaiti, 520, 300, 60, SDL_Color{ 255,255,255 });
			if (time / 60 < 10)
				win->RenderText("0", Font_kaiti, 430, 300, 60, SDL_Color{ 255,255,255 });
		}
	}
}

void gameScene::rend_esc()
{
	boxRGBA(win->getRenderer(), 0, 0, Win_L, Win_H, 0, 0, 0, 100);
	win->RenderText("Esc", Font_kaiti, 280, 160, 150, SDL_Color{ 255,255,255 });
}
