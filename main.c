#include "pathfinding.h"
#include "sdl.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage : %s filename\n", argv[0]);
    return -1;
  }

  srand(time(NULL));
  Position mapSize, tileSize;
  char **map = initArray(argv[1], &mapSize);
  int x, y, wallFind = 0;
  Robot marvin = initRobot(getStartPoint(map, mapSize), mapSize);  // H2G2

  Graph graph = initGraph(mapSize, &tileSize, "carpet.jpg", "wall.jpg",
                          "door.png", "robot.png");

  int windowIsOpen = 1;

  printBack(map, mapSize, tileSize, graph);
  printRobot(marvin.direction, marvin.position, tileSize, graph);
  windowIsOpen = 0;
  while (windowIsOpen) {
    windowIsOpen = handleEvent();
    if (!checkExit(&marvin, map, mapSize)) {
      if (!wallFind) {
        if (checkWall(&marvin, map, mapSize)) {
          turnRight(&marvin);
          wallFind = 1;
        }
      } else {
        searchNextPos(&marvin, map, mapSize);
      }
      clearPosition(marvin.position, graph, tileSize);
      goForward(&marvin, map, mapSize);
    }

    printRobot(marvin.direction, marvin.position, tileSize, graph);
    wait(20);

    printf("\n\n\n");
    for (y = 0; y < mapSize.y; y++) {
      for (x = 0; x < mapSize.x; x++) {
        printf("%c", marvin.memory[y][x]);
      }
      printf("\n");
    }
  }

  aStar();

  printf("Step : %d \n", marvin.step);

  freeGraph(graph);

  freeTab2D((void **)map, mapSize);

  return 0;
}
