#include "sdl.h"

SDL_Surface *initSDL(Position size, Position *tileSize) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) {
    fprintf(stderr, "Erreur init SDL %s\n", SDL_GetError());
    return NULL;
  }

  SDL_Surface *screen =
      SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  if (!screen) {
    fprintf(stderr, "Erreur creation fenetre : %s\n", SDL_GetError());
    return NULL;
  }

  tileSize->x = SCREEN_W / size.x;
  tileSize->y = SCREEN_H / size.y;

  return screen;
}

SDL_Surface *initBackground(char *carpetFile, char *wallFile, char *doorFile,
                            char **map, Position size, Position tileSize) {
  SDL_Surface *back =
      initBlankSurface(size.x * tileSize.x, size.y * tileSize.y);
  SDL_Surface *carpet = IMG_Load(carpetFile);
  SDL_Surface *door = IMG_Load(doorFile);
  SDL_Surface *wall = IMG_Load(wallFile);
  SDL_Rect rect_src;
  int y, x;

  for (y = 0; y < size.y; y++) {
    for (x = 0; x < size.x; x++) {
      // rect_src.x = tileSize.x;
      // rect_src.y = tileSize.y;
      rect_src.w = tileSize.x;
      rect_src.h = tileSize.y;

      switch (map[y][x]) {
        case ' ':
          SDL_BlitSurface(carpet, &rect_src, back, NULL);
          break;
        case 'x':
          SDL_BlitSurface(wall, &rect_src, back, NULL);
          break;
        case 'S':
          SDL_BlitSurface(door, &rect_src, back, NULL);
          break;
      }
    }
  }

  SDL_FreeSurface(carpet);
  SDL_FreeSurface(wall);
  SDL_FreeSurface(door);

  return back;
}

SDL_Surface *initBlankSurface(int width, int height) {
  SDL_Surface *surface;
  Uint32 rmask, gmask, bmask, amask;

/* SDL interprets each pixel as a 32-bit number, so our masks must depend
   on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif

  surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, rmask, gmask,
                                 bmask, amask);
  if (surface == NULL) {
    fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
    return NULL;
  }
  return surface;
}
