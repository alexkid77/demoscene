#pragma once
#include "SDL.H"
#include "SDL_image.h"
#define PI	3.1415926535897932384
#define LOOKUP_SIZE_SIN 1024
class IEffect
{

public:
	IEffect();
	virtual void Init(SDL_Surface *bufferIn)=0;
	virtual void Update(long deltaTime, SDL_Surface *bufferOut) = 0;
	virtual ~IEffect();
};

