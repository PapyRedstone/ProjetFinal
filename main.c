#include "robot.h"
#include "sdl.h"

int main(int argc, char const *argv[]) {
  Position mapSize, *tileSize = malloc(sizeof(Position));
  char **map = initArray("appart.txt", &mapSize);

  // Robot marvin = initRobot(getStartPoint(map, mapSize));
  // turnLeft(&marvin); // H2G2
  // goForward(&marvin);

  // for (int y = 0; y < mapSize.y; y++) {
  //   for (int x = 0; x < mapSize.x; x++) {
  //     if (x == marvin.position.x && y == marvin.position.y) {
  //       printf("R");
  //     } else {
  //       printf("%c", map[y][x]);
  //     }
  //   }
  //   printf("\n");
  // }

  // freeTab2D((void **)map, mapSize);
  SDL_Surface *screen = initSDL(mapSize, tileSize);

  SDL_Surface *back = initBackground("carpet.jpg","wall.jpg", "door.png", map, mapSize, *tileSize);
  
  SDL_BlitSurface(back, NULL, screen, NULL);
  SDL_Flip(screen);
  SDL_Event event;
  int windowIsOpen = 1;
  while (windowIsOpen) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          windowIsOpen = 0;
          break;
      }
    }
  }

  SDL_FreeSurface(screen);
  SDL_FreeSurface(back);

  return 0;
}
