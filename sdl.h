//=============================================================================
//    Fichier de gestion de la partie graphique
//    du robot
//=============================================================================
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "functions.h"

#define SCREEN_W 800
#define SCREEN_H 600

// Initialisaton de la SDL et de la fenetre
SDL_Surface *initSDL(Position size, Position *tileSize);
SDL_Surface *initBackground(char *carpetFile, char *wallFile, char *doorFile,
                            char **map, Position size, Position tileSize);

SDL_Surface *initBlankSurface(int widht, int height);
