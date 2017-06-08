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

Data initData() {
  Data d;
  d.lOpen = malloc(sizeof(Node) * 10);
  d.lClose = malloc(sizeof(Node) * 10);
  d.sizelOpen = 10;
  d.sizelClose = 10;
  d.lastlOpen = 0;
  d.lastlClose = 0;
  return d;
}

Node initNode() {
  Node n;
  n.position.x = -1;
  n.position.y = -1;
  n.prev = NULL;
  n.weigh = INT_MAX;
  return n;
}

int posEgal(Position pos1, Position pos2) {
  return pos1.x == pos2.x && pos1.y == pos2.y;
}

int nodeEgal(Node node1, Node node2) {
  return posEgal(node1.position, node2.position);
}

Node *getPositionNode(Position pos, Data *data) {
  int i;
  Position tmp;
  for (i = 0; i < data->sizelClose; i++) {
    tmp = data->lClose[i].position;
    if (posEgal(tmp, pos)) {
      return &(data->lClose[i]);
    }
  }
  for (i = 0; i < data->sizelOpen; i++) {
    tmp = data->lOpen[i].position;
    if (posEgal(tmp, pos)) {
      return &(data->lOpen[i]);
    }
  }
  return NULL;
}

Node *push_back(Node *array, int *arrayLen, int *lastPos, Node val) {
  if (lastPos >= arrayLen - 1) {
    *arrayLen *= 2;
    array = realloc(array, sizeof(Node) * *arrayLen);
  }
  (*lastPos)++;
  array[*lastPos] = val;
  return array;
}

int isEmpty(Node *array, int arraySize) {
  int i;
  Position tmp;
  tmp.x = INT_MAX;
  tmp.y = INT_MAX;
  for (i = 0; i < arraySize; i++) {
    if (!posEgal(tmp, array[i].position)) {
      return 1;
    }
  }
  return 0;
}

int nodeCompare(void const *a, void const *b){
  const Node *n1 = a;
  const Node *n2 = b;
  return n1->weigh - n2->weigh;
}

int directionTo(Position pos1, Position pos2){
  int x = pos2.x - pos1.x;
  int y = pos2.y - pos1.y;
  if(x > 0){
    return RIGHT;
  }
  else if(x < 0){
    return LEFT;
  }
  else if(y > 0){
    return DOWN;
  }
  else if(y < 0){
    return UP;
  }
  return 0;
}
