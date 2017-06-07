#include "robot.h"
#include "sdl.h"

int main(int argc, char const *argv[]) {
  Position mapSize;
  char **map = initArray("appart.txt", &mapSize);

  Robot marvin = initRobot(getStartPoint(map, mapSize));

  goForward(marvin);

  for (int y = 0; y < mapSize.y; y++) {
    for (int x = 0; x < mapSize.x; x++) {
      if (x == marvin.position.x && y == marvin.position.y) {
        printf("R");
      } else {
        printf("%c", map[y][x]);
      }
    }
    printf("\n");
  }

  freeTab2D((void **)map, mapSize);

  return 0;
}
