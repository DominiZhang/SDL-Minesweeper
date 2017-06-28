#include "Window.h"

#pragma comment(lib,"SDL2_image.lib")
#pragma comment(lib,"SDL2_ttf.lib")

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdexcept>



Window::Window()
{
	//Initialize the unique_ptr's deleters here
	mWindow = nullptr;
	mRenderer = nullptr;
	mPicture = nullptr;
	mMusic = nullptr;
}


Window::~Window()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);

	delete mPicture;
	delete mMusic;
}

/**
*  Initialize SDL, setup the window and renderer
*  @param title The window title
*/
void Window::Init(std::string title, const int SCREEN_WIDTH, const int SCREEN_HEIGHT )
{
	//initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		throw std::runtime_error("SDL Init Failed");
	if (TTF_Init() == -1)
		throw std::runtime_error("TTF Init Failed");
	if (IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF) == -1)
		throw std::runtime_error("IMG Init Failed");

	//Setup our window size
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = SCREEN_WIDTH;
	mBox.h = SCREEN_HEIGHT;
	//Create our window
	mWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mBox.w, mBox.h, SDL_WINDOW_SHOWN);
	//Make sure it created ok
	if (mWindow == nullptr)
		throw std::runtime_error("Failed to create window");

	//Create the renderer
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);//SDL_RENDERER_PRESENTVSYNC 同步垂直 稳定帧数与显示器一样为60帧
	//Make sure it created ok
	if (mRenderer == nullptr)
		throw std::runtime_error("Failed to create renderer");

	//init Picture
	mPicture = new Picture(mRenderer);
	if (mPicture == nullptr)
		throw std::runtime_error("Picture Init Failed");
	
	//init Music
	mMusic = new Music;
	if (mMusic == nullptr)
		throw std::runtime_error("Music Init Failed");

	SDL_SetWindowIcon(mWindow,mPicture->icon);
}

void Window::Quit()
{
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

/**
*  Draw a SDL_Texture to the screen at dstRect with various other options
*  @param tex The SDL_Texture to draw
*  @param dstRect The destination position and width/height to draw the texture with
*  @param clip The clip to apply to the image, if desired
*  @param angle The rotation angle to apply to the texture, default is 0
*  @param xPivot The x coordinate of the pivot, relative to (0, 0) being center of dstRect
*  @param yPivot The y coordinate of the pivot, relative to (0, 0) being center of dstRect
*  @param flip The flip to apply to the image, default is none
*/
void Window::Draw(SDL_Texture * tex, SDL_Rect & dstRect, SDL_Rect * clip, float angle, int xPivot, int yPivot, SDL_RendererFlip flip)
{
	//Convert pivot pos from relative to object's center to screen space
	xPivot += dstRect.w / 2;
	yPivot += dstRect.h / 2;
	//SDL expects an SDL_Point as the pivot location
	SDL_Point pivot = { xPivot, yPivot };
	//Draw the texture
	SDL_RenderCopyEx(mRenderer, tex, clip, &dstRect, angle, &pivot, flip);
}

void Window::Draw(SDL_Texture * tex, int x, int y)
{
	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dstRect.w, &dstRect.h);
	SDL_RenderCopyEx(mRenderer, tex, NULL, &dstRect, 0.0, NULL, SDL_FLIP_NONE);
}

/**
*  Generate a texture containing the message we want to display
*  @param message The message we want to display
*  @param fontFile The font we want to use to render the text
*  @param color The color we want the text to be
*  @param fontSize The size we want the font to be
*  @return An SDL_Texture* to the rendered message
*/
SDL_Texture * Window::RenderText(const std::string & message, const std::string & fontFile, int fontSize, SDL_Color color)
{
	//Open the font
	TTF_Font *font = nullptr;
	font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr)
		throw std::runtime_error("Failed to load font: " + fontFile + TTF_GetError());

	//Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns
	SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer, surf);
	//Clean up unneeded stuff
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);

	return texture;
}

void Window::RenderText(const std::string & message, const std::string & fontFile, int x, int y, int fontSize, SDL_Color color)
{
	SDL_Texture *texture = RenderText(message, fontFile, fontSize, color);
	Draw(texture,x,y);
	SDL_DestroyTexture(texture);
}

void Window::Clear() 
{
	SDL_RenderClear(mRenderer);
}
void Window::Present() 
{
	SDL_RenderPresent(mRenderer);
}
SDL_Rect Window::Box() 
{
	//Update mBox to match the current window size
	SDL_GetWindowSize(mWindow, &mBox.w, &mBox.h);
	return mBox;
}

SDL_Renderer* Window::getRenderer()
{
	return mRenderer;
}



