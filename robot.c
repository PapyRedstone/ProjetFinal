#include "robot.h"

Robot initRobot(Position pos, Position size) {
  Robot rob;
  rob.position = pos;
  rob.direction = UP;
  rob.step = 0;
  rob.path = NULL;
  rob.memory = malloc(size.y * sizeof(char *));
  rob.mapSize = size;
  rob.block = 0;
  rob.firstTour = 1;
  for (int i = 0; i < size.y; i++) {
    rob.memory[i] = malloc(size.x * sizeof(char));
    for (int j = 0; j < size.x; j++) {
      rob.memory[i][j] = ' ';
    }
  }
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

void goForward(Robot *rob, char **map, Position size) {
  if (checkWall(rob, map, size)) {
    return;
  }
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
  rob->memory[rob->position.y][rob->position.x] = '.';
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
  Position pos;
  pos.x = rob->position.x;
  pos.y = rob->position.y;
  switch (rob->direction) {
    case UP:
      pos.y--;
      break;
    case DOWN:
      pos.y++;
      break;

    case LEFT:
      pos.x--;
      break;

    case RIGHT:
      pos.x++;
      break;
  }
  if (posInScreen(pos, size)) {
    return 0;
  }
  if (map[pos.y][pos.x] == 'x') {
    rob->memory[pos.y][pos.x] = 'x';
  }
  return map[pos.y][pos.x] == 'x';
}

int checkChar(Robot *rob, char **map, Position size, char c) {
  Position pos;
  pos.x = rob->position.x;
  pos.y = rob->position.y;
  switch (rob->direction) {
    case UP:
      pos.y--;
      break;
    case DOWN:
      pos.y++;
      break;

    case LEFT:
      pos.x--;
      break;

    case RIGHT:
      pos.x++;
      break;
  }
  if (posInScreen(pos, size)) {
    return 0;
  }
  return map[pos.y][pos.x] == c;
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