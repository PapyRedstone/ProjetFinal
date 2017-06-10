#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "robot.h"

int isLeftAWall(Robot *rob, char **map, Position size);
void followWall(Robot *rob, char **map, Position size);
int robotBlock(Robot *rob);
int searchNextPos(Robot *rob, char **map, Position size);
int positionBlock(Position pos, char **map, Position size);

#endif
