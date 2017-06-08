#include "astar.h"

int heurastique(Position pos1, Position pos2) {
  return abs(pos1.x - pos1.x) + abs(pos1.y - pos2.y);
}

void addAdjacentCase(Robot rob, Data *data, char **map, Position size,
                     Position final) {
  Position relativePos[4];
  int i, j;
  Node tmp;

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
    // definition du point a etudier
    tmp.position.x = rob.position.x + relativePos[i].x;
    tmp.position.y = rob.position.y + relativePos[i].y;
    tmp.prev = getRobotNode(rob, data);
    tmp.weigh = heurastique(tmp.position, final);

    // Verification des bornes
    if (tmp.position.x >= size.x || tmp.position.x < 0 ||
        tmp.position.y >= size.y || tmp.position.y < 0) {
      continue;
    }

    // Verifie que ce n'est pas un mur
    if (map[tmp.position.y][tmp.position.x] == 'x') {
      break;
    }

    // on verifie qu'il n'as pas ete visite
    for (j = 0; j < data->lastlClose; j++) {
      if (nodeEgal(data->lClose[j], tmp)) {
        break;
      }
    }

    // On verifie si il est dans la liste a visiter
    for (j = 0; j < data->lastlOpen; j++) {
      if (nodeEgal(data->lOpen[i], tmp)) {
        //Si il est meilleur que le noeud present on le remplace
        if (tmp.weigh < data->lOpen[i].weigh) {
          data->lOpen[i] = tmp;
        } else {//si il est absent on l'ajoute a la liste a etudier
          if (i >= data->sizelOpen - 1) {
            data->sizelOpen *= 2;
            data->lOpen = realloc(data->lOpen, data->sizelOpen * sizeof(Node));
          }
          data->lOpen[data->lastlOpen++] = tmp;
        }
      }
    }
  }
}