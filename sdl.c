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

  SDL_WM_SetCaption(
      "Robot perdu en perdition dans un appartement perdu qui perdurera (peut "
      "etre)",
      NULL);

  tileSize->x = SCREEN_W / size.x;
  tileSize->y = SCREEN_H / size.y;

  return screen;
}

void printBack(char **map, Position size, Position tileSize, SDL_Surface *screen,
               char *carpet, char *wall, char *door) {
  int y, x;
  float zoom;
  SDL_Surface *img = NULL;
  SDL_Rect src, dest;

  SDL_Surface *carpetSurface = IMG_Load(carpet);
  SDL_Surface *wallSurface = IMG_Load(wall);
  SDL_Surface *doorSurface = IMG_Load(door);

  src.w = tileSize.x;
  src.h = tileSize.y;

  zoom = (float)tileSize.x / IMAGESIZE;

  for (y = 0; y < size.y; y++) {
    for (x = 0; x < size.x; x++) {
      dest.x = x * tileSize.x;
      dest.y = y * tileSize.y;

      src.x = 0;
      src.y = 0;

      switch (map[y][x]) {
        case 'x':
          img = rotozoomSurface(wallSurface, 0.f, zoom, 1);
          break;

        case 'S':
          img = rotozoomSurface(doorSurface, 0.f, zoom, 1);
          break;

        case ' ':
        case 'D':
        default:
          img = rotozoomSurface(carpetSurface, 0.f, zoom, 1);
          break;
      }
      SDL_BlitSurface(img, &src, screen, &dest);
      SDL_FreeSurface(img);
    }
  }
  SDL_Flip(screen);

  SDL_FreeSurface(carpetSurface);
  SDL_FreeSurface(wallSurface);
  SDL_FreeSurface(doorSurface);
}

void printRobot(int direction, Position pos, Position tileSize, SDL_Surface *screen,
                char *robot) {
  SDL_Surface *img = NULL;
  SDL_Rect src, dest;
  SDL_Surface *robotSurface = IMG_Load(robot);

  float zoom, angle;

  zoom = (float)tileSize.x / IMAGESIZE;

  angle = -direction * 90.f;

  img = rotozoomSurface(robotSurface, angle, zoom, 1);

  dest.x = pos.x * tileSize.x;
  dest.y = pos.y * tileSize.y;

  src.w = tileSize.x;
  src.h = tileSize.y;
  src.x = 0;
  src.y = 0;

  SDL_BlitSurface(img, &src, screen, &dest);
  SDL_FreeSurface(img);
  SDL_FreeSurface(robotSurface);
  SDL_Flip(screen);
}