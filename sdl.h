//=============================================================================
//    Fichier de gestion de la partie graphique
//    du robot
//=============================================================================
#ifndef SDL_H
#define SDL_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>
#include "functions.h"

#define SCREEN_W 800
#define SCREEN_H 600
#define IMAGESIZE 64

typedef struct {
  SDL_Surface *screen;
  SDL_Surface *carpet, *wall, *door, *robot;
  Position tileSize;
} Graph;

// Initialisaton de la SDL et de la fenetre
SDL_Surface *initSDL(Position size, Position *tileSize);

// Gestion des donnes de la SDL
Graph initGraph(Position size, char *carpet, char *wall,
                char *door, char *robot);
void freeGraph(Graph g);

// Gestion des evenements
int handleEvent();

// Affichage de l'appartement
void printBack(char **map, Position size, Graph graph);

// Affichahge du robot
void printRobot(int direction, Position pos, Graph graph);

// Nettoyage de l'ancienne position du robot
void clearPosition(Position pos, Graph graph);

// Attente utilisant la SDL
void wait(int time);

#endif
