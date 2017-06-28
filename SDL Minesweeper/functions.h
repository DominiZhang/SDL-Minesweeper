#pragma once
#include "Window.h"

#pragma comment(lib,"SDL2_gfx.lib")

#include "SDL2_gfxPrimitives.h"

//´°¿Ú³ß´ç
#define Win_L 800
#define Win_H 500

//path
#define Font_kaiti "data/Font/simkai.ttf"

bool mainloop(Window *win);
bool recordloop(Window *win);
bool gameloop(Window *win, int level);

void saveHiScore(int time,int level);
int readHiScore(int level);

int Myrand(int max, int min = 0);
