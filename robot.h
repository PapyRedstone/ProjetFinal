//=============================================================================
//    Fichier de gestion de la logique
//    du robot
//=============================================================================
#ifndef ROBOT_H
#define ROBOT_H

#include "functions.h"

// Initialisation du robot
Robot initRobot(Position pos);
Position getStartPoint(char **map, Position size);

// Mouvement du robot
void goForward(Robot *rob, char **map, Position size);
void turnLeft(Robot *rob);
void turnRight(Robot *rob);

// Capteurs du robot
int checkWall(Robot *rob, char **map, Position size);
int checkExit(Robot *rob, char **map, Position size);

#endif
