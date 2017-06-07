#include "robot.h"

Robot initRobot(Position pos) {
  Robot rob;
  rob.position = pos;
  rob.direction = UP;
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

void goForward(Robot rob) {
  switch (rob.direction) {
    case UP:
      rob.position.y--;
      break;
    case DOWN:
      rob.position.y++;
      break;
    case LEFT:
      rob.position.x--;
      break;
    case RIGHT:
      rob.position.x++;
      break;
  }
}