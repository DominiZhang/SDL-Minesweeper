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
	case Gaming:
		if (isclick)
			update_time();
		update_flag();
		if (isWin())
			state = Win;
		break;
	case Win:
		isover = true;
		break;
	case Lose:
		isover = true;
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

	if (state == Gaming)
		rend_cursor();

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
		if ((x >= mapx&&x <= mapx + mapw * 20) && (y >= mapy&&y <= mapy + maph * 20))
		{
			if (!isclick)
				isclick = true;

			digBomb((x - mapx) / 20, (y - mapy) / 20);
		}
	}

	if (events.button.button == SDL_BUTTON_RIGHT)
	{
		if (!isclick)
			isclick = true;

		if ((x >= mapx&&x <= mapx + mapw * 20) && (y >= mapy&&y <= mapy + maph * 20))
		{
			if (map[(x - mapx) / 20][(y - mapy) / 20][1] >= 0)
			{
				map[(x - mapx) / 20][(y - mapy) / 20][1]++;
				if (map[(x - mapx) / 20][(y - mapy) / 20][1] >= 3)
					map[(x - mapx) / 20][(y - mapy) / 20][1] = 0;
			}
		}
	}
}

void gameScene::keyEvent()
{
	switch (events.key.keysym.sym)
	{
	case SDLK_ESCAPE:
		isover = true;
		break;
	}
}

void gameScene::init()
{
	rend_loading();

	isclick = false;

	time = 0;
	time_mm = 0;
	flag = bomb;

	state = Gaming;

	for (int i = 0; i < mapw; i++)
		for (int j = 0; j < maph; j++)
		{
			map[i][j][0] = 0;
			map[i][j][1] = 0;
		}

	setBomb();
	setNum();

}

void gameScene::setBomb()
{
	int i = bomb;
	int x, y;
	while (i)
	{
		x = (Myrand(mapw, 0) + Myrand(mapw, 0)) % mapw;
		y = (Myrand(maph, 0) + Myrand(maph, 0)) % maph;
		if (map[x][y][0] != 9)
		{
			map[x][y][0] = 9;
			i--;
		}
		else
			exploreBomb(i, x, y);
	}
}

void gameScene::exploreBomb(int & num, int x, int y)
{
	int direction = Myrand(8, 0);
	int distance = Myrand(6, 3);
	for (int j = 0; j < 8; j++)
	{
		if ((x + direct[direction][0] + distance >= 0 && x + direct[direction][0] + distance < mapw) && (y + direct[direction][1] + distance >= 0 && y + direct[direction][1] + distance < maph))
			if (map[x + direct[direction][0] + distance][y + direct[direction][1] + distance][0] != 9)
			{
				map[x + direct[direction][0] + distance][y + direct[direction][1] + distance][0] = 9;
				num--;
				return;
			}
		direction--;
		if (direction > 8)
			direction = 0;
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

void gameScene::digBomb(int x, int y)
{
	if (map[x][y][1] == 0|| map[x][y][1] == 2)
	{
		map[x][y][1] = -1;
		if (map[x][y][0] == 9)
		{
			state = Lose;
		}
		else
		{
			surchNum(x, y,1);
		}
	}
}

void gameScene::surchNum(int x, int y,int deep)
{
	for (int k = 0; k < 8; k++)
		if ((x + direct[k][0] >= 0 && x + direct[k][0] < mapw) && (y + direct[k][1] >= 0 && y + direct[k][1] < maph))
		{
			if (map[x + direct[k][0]][y + direct[k][1]][1] == 0|| map[x + direct[k][0]][y + direct[k][1]][1] == 2)
				if (map[x + direct[k][0]][y + direct[k][1]][0] > 0 && map[x + direct[k][0]][y + direct[k][1]][0] < 9)
				{
					if (deep > 1)
						map[x + direct[k][0]][y + direct[k][1]][1] = -1;
				}
				else if (map[x + direct[k][0]][y + direct[k][1]][0] == 0)
				{
					map[x + direct[k][0]][y + direct[k][1]][1] = -1;
					surchNum(x + direct[k][0], y + direct[k][1],deep++);
				}
				else
					break;
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

bool gameScene::isWin()
{
	bool iswin = true;
	int count = 0;
	for (int i = 0; i < mapw; i++)
		for (int j = 0; j < maph; j++)
		{
			if (map[i][j][1] != -1 && map[i][j][0] != 9)
				iswin = false;
			if (map[i][j][1] == 1 && map[i][j][0] == 9)
				count++;
		}
	if(count==bomb)
		iswin = true;
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
