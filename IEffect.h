#pragma once
#include "SDL.H"
#include "SDL_image.h"
class IEffect
{

public:
	IEffect();
	virtual void Init(SDL_Surface *bufferIn)=0;
	virtual void Update(long deltaTime, SDL_Surface *bufferOut) = 0;
	virtual ~IEffect();
};

