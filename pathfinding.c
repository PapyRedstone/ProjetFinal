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

int positionBlock(Position pos, char **map, Position size) {
  Position dir[4];
  int i = 0;

  dir[0].x = pos.x;
  dir[0].y = pos.y - 1;
  dir[1].x = pos.x + 1;
  dir[1].y = pos.y;
  dir[2].x = pos.x;
  dir[2].y = pos.y + 1;
  dir[3].x = pos.x - 1;
  dir[3].y = pos.y;

  for (i = 0; i < 4; i++) {
    if (posInScreen(dir[i], size)) continue;
    if (!(map[dir[i].y][dir[i].x] == 'x' || map[dir[i].y][dir[i].x] == '.')) {
      return 0;
    }
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
    rob->path = rob->path->prev;
  } else {
    followWall(rob, map, size);
    // while(checkChar(rob, rob->memory, rob->mapSize, '.')){
    //   turnLeft(rob);
    // }
  }
  return 1;
}
