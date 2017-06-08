#include "astar.h"

int heurastique(Position pos1, Position pos2) {
  return abs(pos1.x - pos1.x) + abs(pos1.y - pos2.y);
}

void addAdjacentCase(Robot rob, Data *data, char **map, Position size) {
  Position relativePos[4];
  int i;
  Position tmp;

  // Definition des quatres coordonnes a cote du robot
  relativePos[0].x = 1;
  relativePos[0].y = 0;
  relativePos[1].x = -1;
  relativePos[1].y = 0;
  relativePos[2].x = 0;
  relativePos[2].y = 1;
  relativePos[3].x = 0;
  relativePos[3].y = -1;

  for (i = 0; i < 4; i++) {
    tmp.x = rob.position.x + relativePos[i].x;
    tmp.y = rob.position.y + relativePos[i].y;

    //Verification des bornes
    if (tmp.x >= size.x || tmp.x < 0 || tmp.y >= size.y || tmp.y < 0) {
      break;
    }

    //Verifie que ce n'est pas un mur
    if(map[tmp.y][tmp.x] == 'x'){
      break;
    }

  }
}