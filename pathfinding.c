#include "pathfinding.h"

/*=============================================================================
  Fonction : Verifie si la position a droite est un mur ou une position marque
  Entrée: le robot, la carte, la taille de la carte
  Sortie: NEANT
  Retour: boolen(vrai si c'est un mur ou marque, faux sinon)
=============================================================================*/
int isLeftAWall(Robot *rob, char **map, Position size) {
  int result;
  turnLeft(rob);
  result = checkWall(rob, map, size) ||
           checkChar(rob, rob->memory, rob->mapSize, '.');
  turnRight(rob);
  return result;
}

/*=============================================================================
  Fonction : Algorithme "de la main droite" qui suit les murs ET les positions
marques
  Entrée:
  Sortie:
  Retour:
=============================================================================*/
void followWall(Robot *rob, char **map, Position size) {
  if (!isLeftAWall(rob, map, size)) {
    turnLeft(rob);
  }
  if (checkWall(rob, map, size) ||
      checkChar(rob, rob->memory, rob->mapSize, '.')) {
    turnRight(rob);
  }
}

/*=============================================================================
  Fonction :
  Entrée:
  Sortie:
  Retour:
=============================================================================*/
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

/*=============================================================================
  Fonction :
  Entrée:
  Sortie:
  Retour:
=============================================================================*/
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
