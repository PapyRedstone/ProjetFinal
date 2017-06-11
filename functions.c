#include "functions.h"

/*=============================================================================
  Fonction : Recupere une ligne d'une fichier avec verification de retour
correcte et mise de la derniere valeur a '\0'
  Entrée: La ligne a recupere , la taille du buffer, le fichier
  Sortie: NEANT
  Retour: La ligne recupere
=============================================================================*/
char *getFromFile(char *str, int maxLen, FILE *file) {
  char *result = fgets(str, maxLen, file);
  if (!result) {
    fprintf(stderr, "Erreur lecture fichier");
    return NULL;
  }
  str[strlen(str) - 1] = '\0';
  return result;
}

/*=============================================================================
  Fonction : Initialisation d'e la carte
  Entrée: le fichier ou recuperer la carte
  Sortie: la taille de la carte
  Retour: la carte
=============================================================================*/
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

/*=============================================================================
  Fonction : Libere un tableau de deux dimension
  Entrée: Le tableau, sa taille
  Sortie: NEANT
  Retour: NEANT
=============================================================================*/
void freeTab2D(void **tab, Position size) {
  int i;
  for (i = 0; i < size.y; i++) {
    free(tab[i]);
  }
  free(tab);
}

/*=============================================================================
  Fonction : Verifie si deux position sont egales
  Entrée: les deux positions
  Sortie: NEANT
  Retour: un boolean (vrai si les position sont egales, faux sinon)
=============================================================================*/
int posEgal(Position pos1, Position pos2) {
  return pos1.x == pos2.x && pos1.y == pos2.y;
}

/*=============================================================================
  Fonction : Retourne la direction de la position 1 vers la position 2
  Entrée: deux positions
  Sortie: NEANT
  Retour: la direction de 1 vers 2
=============================================================================*/
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

/*=============================================================================
  Fonction : Verifie si la position est dans un rectangle
  Entrée: la position a verifier, la taille du rectangle
  Sortie: NEANT
  Retour: boolean (vrai si la position est dedans, faux sinon)
=============================================================================*/
int posInScreen(Position pos, Position size) {
  return pos.x >= size.x || pos.x < 0 || pos.y >= size.y || pos.y < 0;
}

/*=============================================================================
  Fonction : Ajoute une valeur au debut de la liste chainee
  Entrée: La position a ajouter, la liste chainee a agrandir
  Sortie: NEANT
  Retour: la liste agrandie
=============================================================================*/
Data *addFront(Position pos, Data *data) {
  Data *d = malloc(sizeof(Data));
  d->position = pos;
  if (data) {
    d->directionToPrev = directionTo(pos, data->position);
  } else {
    d->directionToPrev = 0;
  }
  d->prev = data;
  return d;
}

/*=============================================================================
  Fonction : Libere la premiere position d'une liste chainee
  Entrée: La liste a retrecir
  Sortie: NEANT
  Retour: La liste racourcie
=============================================================================*/
Data *popFront(Data *data) {
  if (!data) {
    return NULL;
  }
  Data *tmp = data->prev;
  free(data);
  return tmp;
}

/*=============================================================================
  Fonction : Libere tourte une liste
  Entrée: La liste a liberer
  Sortie: NEANT
  Retour: NEANT
=============================================================================*/
void freeData(Data *data) {
  Data *cur = data;
  while (cur) {
    cur = popFront(cur);
  }
}

/*=============================================================================
  Fonction : Affiche dans la console une carte
  Entrée: La position du robot, la carte, la taille de la carte
  Sortie: NEANT
  Retour: NEANT
=============================================================================*/
void printMap(Position robPos, char **map, Position size) {
  int x, y;
  for (y = 0; y < size.y; y++) {
    for (x = 0; x < size.x; x++) {
      printf("%c", map[y][x]);
      if (x == robPos.x && y == robPos.y) {
        printf("\bR");
      }
    }
    printf("\n");
  }
}
