//=============================================================================
//    Fichier de fonctions utilitaires
//=============================================================================
#ifndef FUNCTION_H
#define FUNCTION_H

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFLEN 1000
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

// Definition d'une structure definissant une position
typedef struct { int x, y; } Position;

// Definition d'une liste chainee contenant une position et une direction pers
// la position precedente
typedef struct Data {
  Position position;
  int directionToPrev;
  struct Data *prev;
} Data;

// Fonction retournant une ligne d'un fichier
char *getFromFile(char *str, int maxLen, FILE *file);

// Gestion du tableau
char **initArray(char *filename, Position *maxPos);
void printMap(Position robPos, char **map, Position size);
void freeTab2D(void **tab, Position size);

// Utilitaire
int posEgal(Position pos1, Position pos2);

int directionTo(Position pos1, Position pos2);
int posInScreen(Position pos, Position size);

// Gestion de la liste chaine
Data *addFront(Position pos, int dir, Data *data);
Data *popFront(Data *data);
void freeData(Data *data);

#endif
