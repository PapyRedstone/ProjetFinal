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

Graph initGraph(Position size, Position *tileSize, char *carpet, char *wall,
                char *door, char *robot) {
  Graph g;
  g.screen = initSDL(size, tileSize);
  g.carpet = IMG_Load(carpet);
  g.wall = IMG_Load(wall);
  g.door = IMG_Load(door);
  g.robot = IMG_Load(robot);
  return g;
}

void freeGraph(Graph g) {
  SDL_FreeSurface(g.wall);
  SDL_FreeSurface(g.door);
  SDL_FreeSurface(g.carpet);
  SDL_FreeSurface(g.robot);
  SDL_FreeSurface(g.screen);
}

void freeSDL(){
  SDL_Quit();
}

int handleEvent() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        return 0;
        break;
    }
  }
  return 1;
}

void printBack(char **map, Position size, Position tileSize, Graph graph) {
  int y, x;
  float zoom;
  SDL_Surface *img = NULL;
  SDL_Rect src, dest;

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
          img = rotozoomSurface(graph.wall, 0.f, zoom, 1);
          break;

        case 'S':
          img = rotozoomSurface(graph.door, 0.f, zoom, 1);
          break;

        case ' ':
        case 'D':
        default:
          img = rotozoomSurface(graph.carpet, 0.f, zoom, 1);
          break;
      }
      SDL_BlitSurface(img, &src, graph.screen, &dest);
      SDL_FreeSurface(img);
    }
  }
  SDL_Flip(graph.screen);
}

void printRobot(int direction, Position pos, Position tileSize, Graph graph) {
  SDL_Surface *img = NULL;
  SDL_Rect src, dest;

  float zoom, angle;

  zoom = (float)tileSize.x / IMAGESIZE;

  angle = -direction * 90.f;

  img = rotozoomSurface(graph.robot, angle, zoom, 1);

  dest.x = pos.x * tileSize.x;
  dest.y = pos.y * tileSize.y;

  src.w = tileSize.x;
  src.h = tileSize.y;
  src.x = 0;
  src.y = 0;

  SDL_BlitSurface(img, &src, graph.screen, &dest);
  SDL_FreeSurface(img);
  SDL_Flip(graph.screen);
}

void clearPosition(Position pos, Graph graph, Position tileSize) {
  SDL_Surface *img = NULL;
  SDL_Rect src, dest;

  float zoom;

  zoom = (float)tileSize.x / IMAGESIZE;

  img = rotozoomSurface(graph.carpet, 0.f, zoom, 1);

  dest.x = pos.x * tileSize.x;
  dest.y = pos.y * tileSize.y;

  src.w = tileSize.x;
  src.h = tileSize.y;
  src.x = 0;
  src.y = 0;

  SDL_BlitSurface(img, &src, graph.screen, &dest);
  SDL_FreeSurface(img);
  SDL_Flip(graph.screen);
}
