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

// Initialisaton de la SDL et de la fenetre
SDL_Surface *initSDL(Position size, Position *tileSize);

// Affichage de l'appartement
void printBack(char **map, Position size, Position tileSize,
               SDL_Surface *screen, char *carpet, char *wall,
               char *door);

// Affichahge du robot
void printRobot(int direction, Position pos, Position tileSize,
                SDL_Surface *screen, char *robot);

#endif
