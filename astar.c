#include "astar.h"

int heurastique(Position pos1, Position pos2) {
  return abs(pos1.x - pos1.x) + abs(pos1.y - pos2.y);
}

void addAdjacentCase(Position pos, Data *data, char **map, Position size,
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

  // printf("%d\n", data->lastlOpen);

  for (i = 0; i < 4; i++) {
    // definition du point a etudier
    tmp.position.x = pos.x + relativePos[i].x;
    tmp.position.y = pos.y + relativePos[i].y;
    tmp.prev = getPositionNode(pos, data);
    tmp.weigh = heurastique(tmp.position, final);

    if (posInScreen(tmp.position, size)) {
      continue;
    }

    // Verifie que ce n'est pas un mur
    if (map[tmp.position.y][tmp.position.x] == 'x') {
      continue;
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
        // Si il est meilleur que le noeud present on le remplace
        if (tmp.weigh < data->lOpen[i].weigh) {
          data->lOpen[i] = tmp;
        } else {  // si il est absent on l'ajoute a la liste a etudier
          data->lOpen = push_back(data->lOpen, &(data->sizelOpen),
                                  &(data->lastlOpen), tmp);
        }
      }
    }
  }
  printf("%d\n", data->lastlOpen);
}

int astar(Robot rob, char **map, Position size, Position final) {
  Data data = initData();
  Node tmp = initNode(), next;
  tmp.position = rob.position;
  addAdjacentCase(tmp.position, &data, map, size, final);
  data.lClose =
      push_back(data.lClose, &(data.sizelClose), &(data.lastlClose), tmp);

  while (!posEgal(tmp.position, final) && isEmpty(data.lOpen, data.lastlOpen)) {
    qsort(data.lOpen, data.lastlOpen, sizeof(Node), &nodeCompare);
    tmp = data.lOpen[0];
    addAdjacentCase(tmp.position, &data, map, size, final);
    data.lClose =
        push_back(data.lClose, &(data.sizelClose), &(data.lastlClose), tmp);
    data.lOpen[0] = initNode();
  }

  if (posEgal(tmp.position, final)) {
    while (posEgal(tmp.position, rob.position)) {
      next = tmp;
      tmp = *tmp.prev;
    }
    return directionTo(tmp.position, next.position);
  }
  printf("No path find\n");
  return 0;
}
