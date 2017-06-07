#include "functions.h"

int **initArray(char *filename, int *x_max, int *y_max){
	FILE *file = fopen(filename,"r");
	if(!file){
		printf("Erreur ouverture du fichier\n");
		return NULL;
	}

	
	
	fclose(file);
}