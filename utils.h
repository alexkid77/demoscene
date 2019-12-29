

#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <stdio.h>
#include <cmath>


typedef struct
{
	float radius;
	float focal_distance;
	float object_distance;
	int x;
	int y;
}SLens;

typedef struct
{
	int *pxPrecal;
	int *pyPrecal;

}SLensPrecal;
SDL_Surface* loadSurface(std::string path, SDL_Surface *buffer);
void drawLens(SDL_Surface *bufferIn, SDL_Surface *bufferOut, SLens *lens);
void drawLensPrecal(SDL_Surface *bufferIn, SDL_Surface *bufferOut, SLens *lens, SLensPrecal *precal);
void LensPrecal(SLens *lens, SLensPrecal *precal);



