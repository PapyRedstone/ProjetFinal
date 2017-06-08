#include "pathfinding.h"

int isLeftAWall(Robot *rob, char **map, Position size){
	int result;
	turnLeft(rob);
	result = checkWall(rob,map,size);
	turnRight(rob);
	return result;
}

void followWall(Robot *rob, char **map, Position size){
	if(!isLeftAWall(rob,map,size)){
		turnLeft(rob);
	}
	if(checkWall(rob,map,size)){
		turnRight(rob);
	}
}
