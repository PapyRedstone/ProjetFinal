#include "sdl.h"

/*=============================================================================
  Fonction: Initialisation de la SDL et creation d'une fenetre
  Entrée: Taille de la carte
  Sortie: Taille d'une tile a l'affichage
  Retour: Une fenetre
=============================================================================*/
SDL_Surface *initSDL(Position size, Position *tileSize) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) {
    fprintf(stderr, "Erreur init SDL %s\n", SDL_GetError());
    return NULL;
  }

  SDL_Surface *screen =
      SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  if (!screen) {
    fprintf(stderr, "Erreur creation fenetre : %s\n", SDL_GetError());
    return NULL;
  }

  SDL_WM_SetCaption(
      "Robot perdu en perdition dans un appartement perdu qui perdurera (peut "
      "etre)",
      NULL);

  tileSize->x = SCREEN_W / size.x;
  tileSize->y = SCREEN_H / size.y;

  return screen;
}

/*=============================================================================
  Fonction: Initialisation d'une structure contenant toutes les informations
graphiques necessaires
  Entrée: Taille de la carte, nom des fichiers pour un tapis, un mur, une porte
et un robot
  Sortie: NEANT
  Retour: Une structure contenatn les informations graphiques
=============================================================================*/
Graph initGraph(Position size, char *carpet, char *wall, char *door,
                char *robot) {
  Graph g;
  g.screen = initSDL(size, &g.tileSize);
  g.carpet = IMG_Load(carpet);
  g.wall = IMG_Load(wall);
  g.door = IMG_Load(door);
  g.robot = IMG_Load(robot);
  return g;
}

/*=============================================================================
  Fonction: Liberation de la memoire d'une structure graphique
  Entrée: une strucutre graphique
  Sortie: NEANT
  Retour: NEANT
=============================================================================*/
void freeGraph(Graph g) {
  SDL_FreeSurface(g.wall);
  SDL_FreeSurface(g.door);
  SDL_FreeSurface(g.carpet);
  SDL_FreeSurface(g.robot);
  SDL_FreeSurface(g.screen);
  SDL_Quit();
}

/*=============================================================================
  Fonction: Gestion des evenement SDL
  Entrée: NEANT
  Sortie: NEANT
  Retour: la fenetre a ete ferme
=============================================================================*/
int handleEvent() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        return 0;
        break;
    }
  }
  return 1;
}

/*=============================================================================
  Fonction: Affichage du fond
  Entrée: La carte utilise, sa taille et la structure graphique
  Sortie: NEANT
  Retour: NEANT
=============================================================================*/
void printBack(char **map, Position size, Graph graph) {
  int y, x;
  float zoom;
  SDL_Surface *img = NULL;
  SDL_Rect src, dest;

  src.w = graph.tileSize.x;
  src.h = graph.tileSize.y;

  zoom = (float)graph.tileSize.x / IMAGESIZE;

  for (y = 0; y < size.y; y++) {
    for (x = 0; x < size.x; x++) {
      dest.x = x * graph.tileSize.x;
      dest.y = y * graph.tileSize.y;

      src.x = 0;
      src.y = 0;

      switch (map[y][x]) {
        case 'x':
          img = rotozoomSurface(graph.wall, 0.f, zoom, 1);
          break;

        case 'S':
          img = rotozoomSurface(graph.door, 0.f, zoom, 1);
          break;

        case ' ':
        case 'D':
        default:
          img = rotozoomSurface(graph.carpet, 0.f, zoom, 1);
          break;
      }
      SDL_BlitSurface(img, &src, graph.screen, &dest);
      SDL_FreeSurface(img);
    }
  }
  SDL_Flip(graph.screen);
}

/*=============================================================================
  Fonction: Affichage du robot
  Entrée: la direction et la position du robot, la sturcture graphique
  Sortie: NEANT
  Retour: NEANT
=============================================================================*/
void printRobot(int direction, Position pos, Graph graph) {
  SDL_Surface *img = NULL;
  SDL_Rect src, dest;

  float zoom, angle;

  zoom = (float)graph.tileSize.x / IMAGESIZE;

  angle = -direction * 90.f;

  img = rotozoomSurface(graph.robot, angle, zoom, 1);

  dest.x = pos.x * graph.tileSize.x;
  dest.y = pos.y * graph.tileSize.y;

  src.w = graph.tileSize.x;
  src.h = graph.tileSize.y;
  src.x = 0;
  src.y = 0;

  SDL_BlitSurface(img, &src, graph.screen, &dest);
  SDL_FreeSurface(img);
  SDL_Flip(graph.screen);
}

/*=============================================================================
  Fonction: Efface le robot
  Entrée: la position a effacer, la strucutre graphique
  Sortie: NEANT
  Retour: NEANT
=============================================================================*/
void clearPosition(Position pos, Graph graph) {
  SDL_Surface *img = NULL;
  SDL_Rect src, dest;

  float zoom;

  zoom = (float)graph.tileSize.x / IMAGESIZE;

  img = rotozoomSurface(graph.carpet, 0.f, zoom, 1);

  dest.x = pos.x * graph.tileSize.x;
  dest.y = pos.y * graph.tileSize.y;

  src.w = graph.tileSize.x;
  src.h = graph.tileSize.y;
  src.x = 0;
  src.y = 0;

  SDL_BlitSurface(img, &src, graph.screen, &dest);
  SDL_FreeSurface(img);
  SDL_Flip(graph.screen);
}

/*=============================================================================
  Fonction: Attendre
  Entrée: Le temps a attendre
  Sortie: NEANT
  Retour: NEANT
=============================================================================*/
void wait(int time) { SDL_Delay(time); }
