#include "Main.h"

int runmode;

SDL_Surface *screen;
int state;
Main mainstruct;
int loading_max = 108;
int loading_progress = 0;

SDL_Window *window = NULL;

void
presentScreen()
{
  SDL_Surface *dst = SDL_GetWindowSurface(window);
  if(dst->w != screen->w || dst->h != screen->h) {
    SDL_Rect r;
    float sx = (float)dst->w / screen->w;
    float sy = (float)dst->h / screen->h;
    float scale = (sx < sy) ? sx : sy;
    r.w = (int)(screen->w * scale);
    r.h = (int)(screen->h * scale);
    r.x = (dst->w - r.w) / 2;
    r.y = (dst->h - r.h) / 2;
    SDL_FillRect(dst, NULL, 0);
    SDL_BlitScaled(screen, NULL, dst, &r);
  } else {
    SDL_BlitSurface(screen, NULL, dst, NULL);
  }
  SDL_UpdateWindowSurface(window);
}

void
testModes()
{
  printf("Video mode testing not available in SDL2.\n");
}

void
showLoadingProgress()
{
  SDL_Rect rect;
  int w = 200, h = 10;

  rect.x = screen->w / 2 - w / 2;
  rect.y = screen->h / 2 - h / 2;
  rect.w = w;
  rect.h = h;
  SDL_FillRect(screen, &rect,
               SDL_MapRGBA(screen->format, 0x40, 0x40, 0x00, 0x00));

  rect.x = screen->w / 2 - w / 2;
  rect.y = screen->h / 2 - h / 2;
  rect.w =
    (int) (((double) w / (double) loading_max) *
           (double) (loading_progress++));
  rect.h = h;
  SDL_FillRect(screen, &rect,
               SDL_MapRGBA(screen->format, 0x80, 0x80, 0x00, 0x00));

  presentScreen();
  if(loading_progress >= loading_max)
    loading_max += 20;
  //SDL_Delay(50);
}

int
main(int argc, char *argv[])
{
  int i;
  int w, h, bpp, n;
  int intro = 0;
  char *mapname;
  int mapwidth, mapheight;

  mainstruct.drawBackground = 1;
  mainstruct.alphaBlend = 1;
  mainstruct.effects_enabled = 1;
  runmode = RUNMODE_SPLASH;
  mainstruct.full_screen = 1;
  
  // my laptop can't handle fullscreen for some reason
#if defined(__APPLE__) || defined(__MACH_O__)
  mainstruct.full_screen = 0;
#endif

  w = 640;
  h = 480;
  bpp = 16;

  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
  }
  atexit(SDL_Quit);
  if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
    fprintf(stderr, "Warning: Audio init failed: %s\n", SDL_GetError());
    sound_enabled = 0;
    music_enabled = 0;
  }

  for(i = 0; i < argc; i++) {
    if(!strcmp(argv[i], "--window")) {
      mainstruct.full_screen = 0;
    } else if(!strcmp(argv[i], "--system") || !strcmp(argv[i], "-s")) {
      /* system memory flag not applicable in SDL2 */
    } else if(!strcmp(argv[i], "--editor") || !strcmp(argv[i], "-e")) {
      runmode = RUNMODE_EDITOR;
    } else if(!strcmp(argv[i], "--nosound")) {
      sound_enabled = 0;
    } else if(!strcmp(argv[i], "--intro") || !strcmp(argv[i], "-i")) {
      runmode = RUNMODE_EDITOR;
      intro = 1;
    } else if(!strcmp(argv[i], "--game") || !strcmp(argv[i], "-g")) {
      runmode = RUNMODE_GAME;
    } else if(!strcmp(argv[i], "--size") && i < argc - 1) {
      n = atoi(argv[i + 1]);
      switch (n) {
      case 0:
        w = 320;
        h = 200;
        break;
      case 1:
        w = 320;
        h = 240;
        break;
      case 2:
        w = 640;
        h = 400;
        break;
      case 3:
        w = 640;
        h = 480;
        break;
      case 4:
        w = 800;
        h = 600;
        break;
      case 5:
        w = 1024;
        h = 768;
        break;
      case 6:
        w = 1280;
        h = 1024;
        break;
      case 7:
        w = 1600;
        h = 1200;
        break;
      default:
        w = 640;
        h = 480;
      }
    } else if((!strcmp(argv[i], "--bpp") || !strcmp(argv[i], "-b"))
              && i < argc - 1) {
      n = atoi(argv[i + 1]);
      if(n == 15 || n == 16 || n == 24 || n == 32)
        bpp = n;
    } else if(!strcmp(argv[i], "--test") || !strcmp(argv[i], "-t")) {
      testModes();
      exit(0);
    } else if(!strcmp(argv[i], "--convert")) {
      convertMap(argv[i + 1], argv[i + 2]);
      exit(0);
    } else if(!strcmp(argv[i], "--help") || !strcmp(argv[i], "-?")
              || !strcmp(argv[i], "-h")) {
      printf("Abe!! Happy Birthday, 2002\n\n");
      printf("--window           Run in windowed mode.\n");
      printf
        ("-e --editor        Skip the splash screen and run the editor.\n");
      printf("-i --intro         Edit intro map.\n");
      printf("-g --game          Skip the splash screen and run the game.\n");
      printf("-t --test          Test video modes only.\n");
      printf
        ("-s --system        Use system memory instead of video(default) memory.\n");
      printf
        ("--size #           Use this width/height for the video mode.\n");
      printf
        ("\tModes: 0-320/200 1-320/240 2-640/400 3-640/480 4-800/600 5-1024/768 6-1280/1024 7-1600/1200\n");
      printf("-b --bpp #         Use this bpp for the video mode.\n");
      printf("--nosound          Don't use sound.\n");
      printf("-? -h --help       Show this help message.\n");
      exit(0);
    }
  }

  // the default map
  if(runmode != RUNMODE_SPLASH && !intro) {
    mapname = strdup("default");
    mapwidth = 1000;
    mapheight = 1000;
  } else {
    mapname = strdup("intro");
    mapwidth = 640 / TILE_W;
    mapheight = 480 / TILE_H;
  }

  fprintf(stderr, "Creating window %dx%d.\n", w, h);
  fflush(stderr);
  {
    Uint32 wflags = SDL_WINDOW_SHOWN;
    if(mainstruct.full_screen)
      wflags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    window = SDL_CreateWindow("Abe's Amazing Adventure!!",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              w, h, wflags);
  }
  if(window == NULL) {
    fprintf(stderr, "Unable to create window: %s\n", SDL_GetError());
    exit(1);
  }
  {
    SDL_Surface *wsurf = SDL_GetWindowSurface(window);
    screen = SDL_CreateRGBSurface(0, w, h,
                                  wsurf->format->BitsPerPixel,
                                  wsurf->format->Rmask, wsurf->format->Gmask,
                                  wsurf->format->Bmask, wsurf->format->Amask);
  }
  if(screen == NULL) {
    fprintf(stderr, "Unable to create virtual screen: %s\n", SDL_GetError());
    exit(1);
  }
  fprintf(stderr, "Success: w=%d h=%d bpp=%d pitch=%d\n", screen->w, screen->h,
          screen->format->BitsPerPixel, screen->pitch);
  fflush(stderr);

  SDL_ShowCursor(0);
  showLoadingProgress();

  initAudio();
  showLoadingProgress();

  initMonsters();
  showLoadingProgress();

  loadImages();
  showLoadingProgress();

  initEditor();
  showLoadingProgress();

  initGame();
  showLoadingProgress();

  if(intro) {
    initMap("intro", 640 / TILE_W, 480 / TILE_H);
    editMap();
  } else {
    showIntro();
  }

  return 0;
}
