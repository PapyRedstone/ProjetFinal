#include "robot.h"

Robot initRobot(Position pos) {
  Robot rob;
  rob.position = pos;
  rob.direction = UP;
  rob.step = 0;
  return rob;
}

Position getStartPoint(char **map, Position size) {
  int x, y;
  for (y = 0; y < size.y; y++) {
    for (x = 0; x < size.x; x++) {
      if (map[y][x] == 'D') {
        Position tmp;
        tmp.x = x;
        tmp.y = y;
        return tmp;
      }
    }
  }
  Position tmp;
  tmp.x = -1;
  tmp.y = -1;
  return tmp;
}

void goForward(Robot *rob) {
  switch (rob->direction) {
    case UP:
      rob->position.y--;
      break;
    case DOWN:
      rob->position.y++;
      break;
    case LEFT:
      rob->position.x--;
      break;
    case RIGHT:
      rob->position.x++;
      break;
  }
  rob->step++;
}

void turnLeft(Robot *rob) {
  rob->direction--;
  if (rob->direction < UP) {
    rob->direction = LEFT;
  }
}
void turnRight(Robot *rob) {
  rob->direction++;
  if (rob->direction > LEFT) {
    rob->direction = UP;
  }
}

int checkWall(Robot *rob, char **map, Position size) {
  int x = rob->position.x;
  int y = rob->position.y;
  switch (rob->direction) {
    case UP:
      y--;
      break;
    case DOWN:
      y++;
      break;

    case LEFT:
      x--;
      break;

    case RIGHT:
      x++;
      break;
  }
  if (x >= size.x || y >= size.y || x < 0 || y < 0) {
    return 0;
  }
  return map[y][x] = 'x';
}

int checkExit(Robot *rob, char **map, Position size) {
  int x = rob->position.x;
  int y = rob->position.y;
  if (map[y - 1][x] == 'S') {
    return 1;
  }
  if (map[y + 1][x] == 'S') {
    return 1;
  }
  if (map[y][x - 1] == 'S') {
    return 1;
  }
  if (map[y][x - 1] == 'S') {
    return 1;
  }
  return 0;
}