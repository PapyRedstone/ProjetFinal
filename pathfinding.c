#include "pathfinding.h"

int isLeftAWall(Robot *rob, char **map, Position size) {
  int result;
  turnLeft(rob);
  result = checkWall(rob, map, size) ||
           checkChar(rob, rob->memory, rob->mapSize, '.');
  turnRight(rob);
  return result;
}

void followWall(Robot *rob, char **map, Position size) {
  if (!isLeftAWall(rob, map, size)) {
    turnLeft(rob);
  }
  if (checkWall(rob, map, size) ||
      checkChar(rob, rob->memory, rob->mapSize, '.')) {
    turnRight(rob);
  }
}

int checkRobotBlock(Robot *rob) {
  int i;
  rob->block = 1;
  for (i = 0; i < 4; i++) {
    if (!(checkChar(rob, rob->memory, rob->mapSize, '.') ||
          checkWall(rob, rob->memory, rob->mapSize))) {
      rob->block = 0;
      return 0;
    }
    turnLeft(rob);
  }
  return 1;
}

int searchNextPos(Robot *rob, char **map, Position size) {
  if (!rob->path) {
    return 0;
  }
  if (checkRobotBlock(rob)) {
    while (rob->direction != rob->path->directionToPrev) {
      turnRight(rob);
    }
    rob->path = popFront(rob->path);
  } else {
    followWall(rob, map, size);
  }
  return 1;
}
