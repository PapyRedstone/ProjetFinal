//=============================================================================
//		Fichier de gestion de la logique
//		du robot
//=============================================================================
#include "functions.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

typedef struct{
  int direction;
  Position position; 
}Robot;

Robot initRobot(Position pos);
Position getStartPoint(char **map, Position size);
void goForward(Robot rob);