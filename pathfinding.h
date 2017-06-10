#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "robot.h"

// verifie si le mur a droite est un mur
int isLeftAWall(Robot *rob, char **map, Position size);

// Suis le mur et les positions marques
void followWall(Robot *rob, char **map, Position size);

// Verifie si le robot est entoure par des murs et/ou des positions marques
int robotBlock(Robot *rob);

// Oriente le robot dans la direction du prochain deplacement
int searchNextPos(Robot *rob, char **map, Position size);

#endif
