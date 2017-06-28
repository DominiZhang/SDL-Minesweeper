#include "Picture.h"

#pragma comment(lib,"SDL2_image.lib")
#include <SDL_image.h>
#include <stdexcept>

Picture::Picture(SDL_Renderer *Ren) :Renderer(Ren)
{
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	icon = IMG_Load("data/Picture/icon/icon.png");

	easy = LoadImage("data/Picture/button/easy.png");
	medium = LoadImage("data/Picture/button/medium.png");
	expert = LoadImage("data/Picture/button/expert.png");
	highest = LoadImage("data/Picture/button/highest.png");
	escape = LoadImage("data/Picture/button/escape.png");

	num1 = LoadImage("data/Picture/number/1.png");
	num2 = LoadImage("data/Picture/number/2.png");
	num3 = LoadImage("data/Picture/number/3.png");
	num4 = LoadImage("data/Picture/number/4.png");
	num5 = LoadImage("data/Picture/number/5.png");
	num6 = LoadImage("data/Picture/number/6.png");
	num7 = LoadImage("data/Picture/number/7.png");
	num8 = LoadImage("data/Picture/number/8.png");

	bomb = LoadImage("data/Picture/other/bomb.png");
	flag = LoadImage("data/Picture/other/flag.png");
	grass = LoadImage("data/Picture/other/grass.png");
	land = LoadImage("data/Picture/other/land.png");
	unknown = LoadImage("data/Picture/other/unknown.png");

	cursor = LoadImage("data/Picture/other/cursor.png");

	bomb_logo = LoadImage("data/Picture/other/bomb_logo.png");
	timer_logo = LoadImage("data/Picture/other/timer_logo.png");
	gameBackground = LoadImage("data/Picture/other/gameBackground.png");
	loading = LoadImage("data/Picture/other/loading.png");
}


Picture::~Picture()
{
	SDL_FreeSurface(icon);

	delimage(easy);
	delimage(medium);
	delimage(expert);
	delimage(highest);
	delimage(escape);

	delimage(num1);
	delimage(num2);
	delimage(num3);
	delimage(num4);
	delimage(num5);
	delimage(num6);
	delimage(num7);
	delimage(num8);

	delimage(bomb);
	delimage(flag);
	delimage(grass);
	delimage(land);
	delimage(unknown);

	delimage(cursor);

	delimage(bomb_logo);
	delimage(timer_logo);
	delimage(gameBackground);
	delimage(loading);
}

/**
*  Loads an image directly to texture using SDL_image's
*  built in function IMG_LoadTexture
*  @param file The image file to load
*  @return SDL_Texture* to the loaded texture
*/
SDL_Texture * Picture::LoadImage(const std::string & file)
{
	SDL_Texture *texture = IMG_LoadTexture(Renderer, file.c_str());
	if (texture == nullptr) {
		throw std::runtime_error("LoadTexture");
	}
	return texture;
}

void Picture::delimage(SDL_Texture * image)
{
	SDL_DestroyTexture(image);
}
