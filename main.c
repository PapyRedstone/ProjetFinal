#include "pathfinding.h"
#include "sdl.h"

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  Position mapSize, tileSize, exitPos;
  char **map = initArray("appart.txt", &mapSize);
  int x, y, tmp = 1;
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

  char *robot = "robot.png";
  char *wall = "wall.jpg";
  char *door = "door.png";
  char *carpet = "carpet.jpg";

  SDL_Event event;
  int windowIsOpen = 1;

  printBack(map, mapSize, tileSize, screen, carpet, wall, door);
  printRobot(marvin.direction, marvin.position, tileSize, screen, robot);

  while (windowIsOpen) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          windowIsOpen = 0;
          break;
      }
    }
    if (!checkExit(&marvin, map, mapSize)) {
      if (tmp) {
        if (checkWall(&marvin, map, mapSize)) {
          turnRight(&marvin);
          tmp = 0;
        }
      } else {
        followWall(&marvin, map, mapSize);
      }
      goForward(&marvin, map, mapSize);
    }

    printBack(map, mapSize, tileSize, screen, carpet, wall,
              door);
    printRobot(marvin.direction, marvin.position, tileSize, screen,
               robot);
  }

  printf("Step : %d \n", marvin.step);

  SDL_FreeSurface(screen);

  freeTab2D((void **)map, mapSize);

  SDL_Quit();

  return 0;
}
