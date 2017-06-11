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
  int wallFind = 0;
  Robot marvin = initRobot(getStartPoint(map, mapSize), mapSize);  // H2G2

  Graph graph = initGraph(mapSize, &tileSize, "carpet.jpg", "wall.jpg",
                          "door.png", "robot.png");

  int windowIsOpen = 1;

  printBack(map, mapSize, tileSize, graph);
  printRobot(marvin.direction, marvin.position, tileSize, graph);

  while (windowIsOpen) {
    printf("\n\n\n");
    printMap(marvin.position, marvin.memory, marvin.mapSize);
    windowIsOpen = handleEvent();
    if (!checkExit(&marvin, map, mapSize)) {
      if (!wallFind) {
        if (checkWall(&marvin, map, mapSize)) {
          turnRight(&marvin);
          wallFind = 1;
        }
      } else {
        if (!searchNextPos(&marvin, map, mapSize)) {
          printf("No Exit Found\n");
          windowIsOpen = 0;
        }
      }
      clearPosition(marvin.position, graph, tileSize);
      goForward(&marvin, map, mapSize);
      if (!marvin.block) {
        marvin.path =
            addFront(marvin.position, (marvin.direction + 2) % 4, marvin.path);
      }
    } else {
      printf("Exit Found !\n");
      windowIsOpen = 0;
    }

    printRobot(marvin.direction, marvin.position, tileSize, graph);
    wait(20);
  }

  printf("Step : %d \n", marvin.step);

  freeGraph(graph);

  deleteRobot(&marvin);

  freeTab2D((void **)map, mapSize);

  return 0;
}
