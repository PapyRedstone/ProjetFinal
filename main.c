#include "pathfinding.h"
#include "sdl.h"

int main(int argc, char *argv[]) {
  // verification du nombre de parametre
  if (argc != 2) {
    fprintf(stderr, "Usage : %s filename\n", argv[0]);
    return -1;
  }

  srand(time(NULL));

  // declaration et initialisation des variables
  Position mapSize;
  char **map = initArray(argv[1], &mapSize);
  Robot marvin = initRobot(getStartPoint(map, mapSize), mapSize);  // H2G2

  Graph graph =
      initGraph(mapSize, "carpet.jpg", "wall.jpg", "door.png", "robot.png");

  int windowIsOpen = 1;

  // premier affichage
  printBack(map, mapSize, graph);
  printRobot(marvin.direction, marvin.position, graph);

  while (windowIsOpen) {
    // Affichage de la memoire du robot
    printf("\n");
    printMap(marvin.position, marvin.memory, marvin.mapSize);
    windowIsOpen = handleEvent();

    clearPosition(marvin.position, ' ', graph);

    // Recerche de la prochaine position
    if (!checkExit(&marvin, map, mapSize)) {
      // cas ou in a plus de pas possible
      if (!searchNextPos(&marvin, map, mapSize)) {
        printf("No Exit Found\n");
        windowIsOpen = 0;
      }

      // on avanche et on sauvegarde ce mouvement
      goForward(&marvin, map, mapSize);
      if (!marvin.block) {
        marvin.path = addFront(marvin.position, marvin.path);
      }
    } else {  // cas ou on a trouve la sortie
      printf("Exit Found !\n");
      windowIsOpen = 0;
    }

    printRobot(marvin.direction, marvin.position, graph);

    wait(DELAY);
  }

  printf("Step : %d \n", marvin.step);

  // Liberation de la memoire
  freeGraph(graph);

  deleteRobot(&marvin);

  freeTab2D((void **)map, mapSize);

  return 0;
}
