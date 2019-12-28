#pragma once
#include "IEffect.h"
#include <string>
#include <stdio.h>
#include <math.h>


class CLensEffect :
	public IEffect
{
private:
	
	



	/*vector of precalculated data of the len*/
	int *pxPrecal;
	int *pyPrecal;
	SDL_Surface *bufferIn;
	/*bufferIN*/

	/*do the precalculations of the data*/
	void LensPrecal();
	void drawLensPrecal( SDL_Surface *bufferOut);
	void drawLens(SDL_Surface *bufferOut);
public:

	/*values of the len*/
	float radius;
	float focal_distance;
	float object_distance;
	/*position the len*/
	int x;
	int y;

	CLensEffect();
	CLensEffect(float radius, float focalDistance, float objectDistance);
	void Init(SDL_Surface *bufferIn);
	void Update(long deltaTime,  SDL_Surface *bufferOut);
	~CLensEffect();
};

