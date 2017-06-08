//=============================================================================
//    Fichier de fonctions utilitaires
//=============================================================================
#ifndef FUNCTION_H
#define FUNCTION_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define BUFFLEN 1000
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

typedef struct { int x, y; } Position;



// Fonction retournant une ligne d'un fichier
char *getFromFile(char *str, int maxLen, FILE *file);

// Gestion du tableau
char **initArray(char *filename, Position *maxPos);
void freeTab2D(void **tab, Position size);

// Utilitaire
int posEgal(Position pos1, Position pos2);

int directionTo(Position pos1, Position pos2);
int posInScreen(Position pos, Position size);

#endif
