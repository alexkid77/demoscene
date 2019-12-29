#pragma once
#include "IEffect.h"
#include <cmath>
class CRotozoom :
	public IEffect
{
private:
	SDL_Surface *texture;
	float ang;
	float zoom;

	long double sin_t[LOOKUP_SIZE_SIN];
	long double cos_t[LOOKUP_SIZE_SIN];
public:
	
	void Init(SDL_Surface *bufferIn) ;
	
	void generateLookupSinCosTables();
	void Update(long deltaTime, SDL_Surface *bufferOut);
	CRotozoom();
	~CRotozoom();
	void RotoZoom(SDL_Surface * buffer, SDL_Surface * texture, float ang, float zoom, long double * cos_t, long double * sin_t);

	inline void setAng(float a)
	{
		this->ang = a;
	}

	inline void setZoom(float z)
	{
		this->zoom = z;
	}
};

