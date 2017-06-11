#include "robot.h"


/*=============================================================================
  Fonction : Initialise le robot
  Entrée: La position de depart et la position de la carte
  Sortie: NEANT
  Retour: Le robot
=============================================================================*/
Robot initRobot(Position pos, Position size) {
  Robot rob;
  rob.position = pos;
  rob.direction = UP;
  rob.step = 0;
  rob.memory = malloc(size.y * sizeof(char *));
  rob.mapSize = size;
  rob.block = 0;
  for (int i = 0; i < size.y; i++) {
    rob.memory[i] = malloc(size.x * sizeof(char));
    for (int j = 0; j < size.x; j++) {
      rob.memory[i][j] = ' ';
    }
  }
  rob.path = addFront(rob.position, NULL);
  return rob;
}

/*=============================================================================
  Fonction : Supprime le robot
  Entrée: le robot
  Sortie: NEANT
  Retour: NEATN
=============================================================================*/
void deleteRobot(Robot *rob) {
  int i;
  freeData(rob->path);
  for (i = 0; i < rob->mapSize.y; i++) {
    free(rob->memory[i]);
  }
  free(rob->memory);
}


/*=============================================================================
  Fonction : Recupere le point de depart du robot
  Entrée: la carte, la taille de sa carte
  Sortie: NEANT
  Retour: la position de depart du robot 
=============================================================================*/
Position getStartPoint(char **map, Position size) {
  int x, y;
  Position tmp;
  for (y = 0; y < size.y; y++) {
    for (x = 0; x < size.x; x++) {
      if (map[y][x] == 'D') {
        tmp.x = x;
        tmp.y = y;
        return tmp;
      }
    }
  }
  tmp.x = -1;
  tmp.y = -1;
  return tmp;
}


/*=============================================================================
  Fonction : Fait avancer le robot
  Entrée: le robot, la carte, la taille de la carte
  Sortie: le Robot
  Retour: NEANT
=============================================================================*/
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


/*=============================================================================
  Fonction : Tourne a gauche
  Entrée: le robot
  Sortie: le robot
  Retour: NEANT
=============================================================================*/
void turnLeft(Robot *rob) {
  rob->direction--;
  if (rob->direction < UP) {
    rob->direction = LEFT;
  }
}


/*=============================================================================
  Fonction : Tourne a droite
  Entrée: le robot
  Sortie: le robot
  Retour: NEANT
=============================================================================*/
void turnRight(Robot *rob) {
  rob->direction++;
  if (rob->direction > LEFT) {
    rob->direction = UP;
  }
}


/*=============================================================================
  Fonction : Verifie si la case en face du robot est un mur
  Entrée: le robot, la carte, la taille de la carte
  Sortie: NEANT
  Retour: boolean (vraie si c'est un mur, faux sinon)
=============================================================================*/
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

/*=============================================================================
  Fonction : Verifie si la case en face du robot est un certain caratere
  Entrée: le robot, la carte, la taille de la carte
  Sortie: NEANT
  Retour: boolean (vraie si c'est un caractere, faux sinon)
=============================================================================*/
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

/*=============================================================================
  Fonction : Verifie si la sortie est a cote du robot
  Entrée: le robot
  Sortie: NEANT
  Retour: boolean (vraie si c'est un pur, faux sinon)
=============================================================================*/
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