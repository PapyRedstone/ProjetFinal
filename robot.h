//=============================================================================
//    Fichier de gestion de la logique
//    du robot
//=============================================================================
#ifndef ROBOT_H
#define ROBOT_H

#include "functions.h"

typedef struct {
  int direction, block;
  Position position, mapSize;
  unsigned step;
  char **memory;
  Data *path;
} Robot;

// Gestion du robot
Robot initRobot(Position pos, Position size);
void deleteRobot(Robot *rob);
Position getStartPoint(char **map, Position size);

// Mouvement du robot
void goForward(Robot *rob, char **map, Position size);
void turnLeft(Robot *rob);
void turnRight(Robot *rob);

// Capteurs du robot
int checkWall(Robot *rob, char **map, Position size);
int checkExit(Robot *rob, char **map, Position size);

//Memoire du robot
int checkChar(Robot *rob, char **map, Position size, char c);


#endif
