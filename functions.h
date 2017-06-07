//=============================================================================
//		Fichier de fonctions utilitaires 
//=============================================================================
#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define BUFFLEN 1000

typedef struct{
	int x,y;
} Position;

//Fonction retournant une ligne d'un fichier
char *getFromFile(char *str, int maxLen, FILE *file);

char **initArray(char *filename, Position *maxPos);
void freeTab2D(void **tab, Position size);

#endif
