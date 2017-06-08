//=============================================================================
//    Fichier de l'algorithme A*
//=============================================================================
#ifndef ASTAR_H
#define ASTAR_H

#include "robot.h"

// Fonctions d'aides pour A*
int heurastique(Position pos1, Position pos2);
void addAdjacentCase(Robot rob, Data *data, char **map, Position size,
                     Position final);

#endif
