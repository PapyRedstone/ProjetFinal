#include "pathfinding.h"
#include "sdl.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage : %s filename\n", argv[0]);
    return -1;
  }

  Position mapSize;
  char **map = initArray(argv[1], &mapSize);
  Robot marvin = initRobot(getStartPoint(map, mapSize), mapSize);  // H2G2
  Robot nono = initRobot(getStartPoint(map, mapSize), mapSize);  

  nono.position.x = 16;
  nono.position.y = 35;

  Graph graph = initGraph(mapSize, "carpet.jpg", "wall.jpg",
                          "door.png", "robot.png");

  int windowIsOpen = 1;

  printBack(map, mapSize, graph);
  printRobot(marvin.direction, marvin.position, graph);
  printRobot(nono.direction, nono.position, graph);

  while (windowIsOpen) {
    // Affichage de la memoire du robot
    //printf("\n\n\n");
    //printMap(marvin.position, marvin.memory, marvin.mapSize);
    //printMap(nono.position, nono.memory, marvin.mapSize);
    windowIsOpen = handleEvent();

    clearPosition(marvin.position, graph);
    clearPosition(nono.position, graph);

    // Recerche de la prochaine position
    if (!checkExit(&marvin, map, mapSize) || !checkExit(&nono, map, mapSize)) {
      // cas ou in a plus de pas possible
      searchNextPos(&nono, map, mapSize);
      if (!searchNextPos(&marvin, map, mapSize)) {
        printf("No Exit Found\n");
        windowIsOpen = 0;
      }

      // on avanche et on sauvegarde ce mouvement
      goForward(&marvin, map, mapSize);
      if (!marvin.block) {
        marvin.path =
            addFront(marvin.position, marvin.path);
      }

      goForward(&nono, map, mapSize);
      if (!nono.block) {
        nono.path =
            addFront(nono.position, nono.path);
      }
    } else {  // cas ou on a trouve la sortie
      printf("Exit Found !\n");
      windowIsOpen = 0;
    }

    printRobot(marvin.direction, marvin.position, graph);
    printRobot(nono.direction, nono.position, graph);
    wait(20);
  }

  printf("Step : %d \n", marvin.step);

  freeGraph(graph);

  deleteRobot(&marvin);
  deleteRobot(&nono);

  freeTab2D((void **)map, mapSize);

  return 0;
}
