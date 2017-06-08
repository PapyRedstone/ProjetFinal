#include "astar.h"
#include "sdl.h"

int main(int argc, char const *argv[]) {
  Position mapSize, tileSize, exitPos;
  char **map = initArray("appart.txt", &mapSize);
  int x, y;
  Robot marvin = initRobot(getStartPoint(map, mapSize));  // H2G2

  for (y = 0; y < mapSize.y; y++) {
    for (x = 0; x < mapSize.x; x++) {
      if (map[y][x] == 'S') {
        exitPos.x = x;
        exitPos.y = y;
      }
    }
  }

  SDL_Surface *screen = initSDL(mapSize, &tileSize);

  SDL_Surface *carpetSurface = IMG_Load("carpet.jpg");
  SDL_Surface *wallSurface = IMG_Load("wall.jpg");
  SDL_Surface *doorSurface = IMG_Load("door.png");
  SDL_Surface *robotSurface = IMG_Load("robot.png");

  SDL_Event event;
  int windowIsOpen = 1;

  printBack(map, mapSize, tileSize, screen, carpetSurface, wallSurface,
            doorSurface);
  printRobot(marvin.direction, marvin.position, tileSize, screen, robotSurface);

  while (windowIsOpen) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          windowIsOpen = 0;
          break;
      }
    }

    int dir = astar(marvin, map, mapSize, exitPos);

    while (dir != marvin.direction) {
      turnLeft(&marvin);
    }

    goForward(&marvin, map, mapSize);

    printf("%d : %d \n", marvin.position.x, marvin.position.y);

    printBack(map, mapSize, tileSize, screen, carpetSurface, wallSurface,
              doorSurface);
    printRobot(marvin.direction, marvin.position, tileSize, screen,
               robotSurface);
  }

  SDL_FreeSurface(screen);
  SDL_FreeSurface(carpetSurface);
  SDL_FreeSurface(wallSurface);
  SDL_FreeSurface(doorSurface);
  SDL_FreeSurface(robotSurface);

  freeTab2D((void **)map, mapSize);

  SDL_Quit();

  return 0;
}
