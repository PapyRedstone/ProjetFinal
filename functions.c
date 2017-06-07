#include "functions.h"

char *getFromFile(char *str, int maxLen, FILE *file) {
  char *result = fgets(str, maxLen, file);
  if (!result) {
    fprintf(stderr, "Erreur lecture fichier");
    return NULL;
  }
  str[strlen(str) - 1] = '\0';
  return result;
}

char **initArray(char *filename, Position *size) {
  FILE *file = fopen(filename, "r");
  int x, y;
  char ligne[BUFFLEN];
  char **array = NULL;

  if (!file) {
    fprintf(stderr, "Erreur ouverture du fichier\n");
    return NULL;
  }

  // Recuperation de la taille de l'appartement
  getFromFile(ligne, BUFFLEN, file);
  size->y = atoi(strchr(ligne, ':') + 1);
  ligne[strchr(ligne, ':') - ligne] = '\0';
  size->x = atoi(ligne);

  // Allocation memoire du tableau
  if (!(array = malloc(sizeof(char *) * size->y))) {
    fprintf(stderr, "Erreur allocation memoire");
    return NULL;
  }

  // Recuperation des donnes du fichier
  for (y = 0; y < size->y; y++) {
    if (!getFromFile(ligne, BUFFLEN, file)) {
      return NULL;
    }
    if (!(array[y] = malloc(sizeof(char) * size->x))) {
      fprintf(stderr, "Erreur allocation memoire");
      return NULL;
    }
    for (x = 0; x < size->x; x++) {
      array[y][x] = ligne[x];
    }
  }

  fclose(file);

  return array;
}

void freeTab2D(void **tab, Position size) {
  int i;
  for (i = 0; i < size.y; i++) {
    free(tab[i]);
  }
  free(tab);
}