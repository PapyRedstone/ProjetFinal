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

  Graph graph = initGraph(mapSize, &tileSize, "carpet.jpg", "wall.jpg",
                          "door.png", "robot.png");

  int windowIsOpen = 1;

  printBack(map, mapSize, tileSize, graph);
  printRobot(marvin.direction, marvin.position, tileSize, graph);

  while (windowIsOpen) {
    windowIsOpen = handleEvent();
    if (!checkExit(&marvin, map, mapSize)) {
      if (tmp) {
        if (checkWall(&marvin, map, mapSize)) {
          turnRight(&marvin);
          tmp = 0;
        }
      } else {
        followWall(&marvin, map, mapSize);
      }
      clearPosition(marvin.position, graph, tileSize);
      goForward(&marvin, map, mapSize);
    }

    printRobot(marvin.direction, marvin.position, tileSize, graph);
    SDL_Delay(25);
  }

  printf("Step : %d \n", marvin.step);

  freeGraph(graph);

  freeTab2D((void **)map, mapSize);

  freeSDL();

  return 0;
}
