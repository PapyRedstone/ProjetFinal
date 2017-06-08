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

#define BUFFLEN 1000

typedef struct { int x, y; } Position;

typedef struct {
  Position *lOpen, *lClose;
  int sizelOpen, sizelClose;
  int lastlOpen, lastlClose;
} Data;

typedef struct {
  int direction;
  Position position;
  unsigned step;
  Data data;
} Robot;

// Fonction retournant une ligne d'un fichier
char *getFromFile(char *str, int maxLen, FILE *file);

//Gestion des datas
Data initData();


//Gestion du tableau
char **initArray(char *filename, Position *maxPos);
void freeTab2D(void **tab, Position size);

#endif
