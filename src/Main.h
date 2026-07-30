#ifndef MAIN_H
#define MAIN_H


#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_mixer.h>

#include "Common.h"
#include "Image.h"
#include "Font.h"
#include "Util.h"
#include "Sound.h"
#include "Splash.h"
#include "Menu.h"
#include "Map.h"
#include "MapIO.h"
#include "Monster.h"
#include "Editor.h"
#include "Game.h"

#define RUNMODE_SPLASH 0
#define RUNMODE_EDITOR 1
#define RUNMODE_GAME 2

extern int runmode;

extern SDL_Surface *screen;
extern SDL_Window *window;
extern int state;

typedef struct _main {
  int drawBackground;
  int full_screen;
  int alphaBlend;
  int effects_enabled;
} Main;
extern Main mainstruct;

void startEditor();
void startGame();
void showLoadingProgress();
void presentScreen(void);

#endif
