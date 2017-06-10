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

int posEgal(Position pos1, Position pos2) {
  return pos1.x == pos2.x && pos1.y == pos2.y;
}

int directionTo(Position pos1, Position pos2) {
  int x = pos2.x - pos1.x;
  int y = pos2.y - pos1.y;
  if (x > 0) {
    return RIGHT;
  } else if (x < 0) {
    return LEFT;
  } else if (y > 0) {
    return DOWN;
  } else if (y < 0) {
    return UP;
  }
  return 0;
}

int posInScreen(Position pos, Position size) {
  return pos.x >= size.x || pos.x < 0 || pos.y >= size.y || pos.y < 0;
}

Data *addFront(Position pos, int dir,Data *data) {
  Data *d = malloc(sizeof(Data));
  d->position = pos;
  d->directionToPrev = dir;
  d->prev = data;
  return d;
}

Data *popFront(Data *data) {
  Data *tmp = data->prev;
  free(data);
  return tmp;
}

void freeData(Data *data) {
  Data *cur = data;
  while (cur) {
    popFront(cur);
  }
}
