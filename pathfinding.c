#include "pathfinding.h"

int isLeftAWall(Robot *rob, char **map, Position size) {
  int result;
  turnLeft(rob);
  result = checkWall(rob, map, size);
  turnRight(rob);
  return result;
}

void followWall(Robot *rob, char **map, Position size) {
  if (!isLeftAWall(rob, map, size)) {
    turnLeft(rob);
  }
  if (checkWall(rob, map, size)) {
    turnRight(rob);
  }
}

int robotBlock(Robot *rob) {
  int i;
  for (i = 0; i < 4; i++) {
    if (!(checkChar(rob, rob->memory, rob->mapSize, '.') ||
          checkWall(rob, rob->memory, rob->mapSize))) {
      rob->block = 0; return 0;
    }
    turnLeft(rob);
  }
  rob->block = 1;
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

void searchNextPos(Robot *rob, char **map, Position size) {
  rob->path = addFront(rob->position, rob->path);
  int result;

  robotBlock(rob);
  // Si le robot est bloque on revient sur ses pas
  if (rob->block) {
    while (positionBlock(rob->path->position, rob->memory, rob->mapSize)) {
      rob->path = popFront(rob->path);
    }
    printf("%d : %d\n", rob->path->position.x, rob->path->position.y);
    while (rob->direction != directionTo(rob->position, rob->path->position)) {
      turnLeft(rob);
    }
  } else {
    // verifie si on a fait 1 tour
    if (checkChar(rob, rob->memory, size, '.') && rob->firstTour) {
      rob->firstTour = 0;
    }

    // si on a pas fait 1 tour on suit le mur
    if (rob->firstTour) {
      followWall(rob, map, size);
    } else {  // si on a fait plus de 1 tour on evite de repasser par les points
              // deja visite
      turnLeft(rob);
      result =
          checkChar(rob, rob->memory, size, '.') || checkWall(rob, map, size);
      turnRight(rob);
      if (!result) {
        turnLeft(rob);
      }
      if (checkChar(rob, rob->memory, size, '.') || checkWall(rob, map, size)) {
        turnRight(rob);
      }
    }
  }
}
