#pragma once

#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")

#include <SDL.h>

#include <stdexcept>
#include <string>

class Picture
{
public:
	Picture(SDL_Renderer *Ren);
	~Picture();

	//Load an image
	SDL_Texture * Picture::LoadImage(const std::string & file);
	void delimage(SDL_Texture* image);

private:
	SDL_Renderer *Renderer=nullptr;

public:
	SDL_Surface *icon = nullptr;

	SDL_Texture *easy = nullptr;
	SDL_Texture *medium = nullptr;
	SDL_Texture *expert = nullptr;
	SDL_Texture *highest = nullptr;
	SDL_Texture *escape = nullptr;

	SDL_Texture *num1 = nullptr;
	SDL_Texture *num2 = nullptr;
	SDL_Texture *num3 = nullptr;
	SDL_Texture *num4 = nullptr;
	SDL_Texture *num5 = nullptr;
	SDL_Texture *num6 = nullptr;
	SDL_Texture *num7 = nullptr;
	SDL_Texture *num8 = nullptr;

	SDL_Texture *bomb = nullptr;
	SDL_Texture *flag = nullptr;
	SDL_Texture *grass = nullptr;
	SDL_Texture *land = nullptr;
	SDL_Texture *unknown = nullptr;

	SDL_Texture *cursor = nullptr;

	SDL_Texture *bomb_logo = nullptr;
	SDL_Texture *timer_logo = nullptr;
	SDL_Texture *gameBackground = nullptr;
	SDL_Texture *loading = nullptr;
	SDL_Texture *OpenAD = nullptr;
};

