#include "CRotozoom.h"


 
void CRotozoom::Init(SDL_Surface * texture)
{
	this->texture = texture;

	this->generateLookupSinCosTables();
	this->ang = 0;
}

void CRotozoom::generateLookupSinCosTables()
{
	for (int index = 0; index < LOOKUP_SIZE_SIN; index++)
		this->sin_t[index] = std::sin(PI * 2 * index / LOOKUP_SIZE_SIN);
	

	for (int index = 0; index < LOOKUP_SIZE_SIN; index++)
	
		this->cos_t[index] = std::cos(PI * 2 * index / LOOKUP_SIZE_SIN);
	
}

void CRotozoom::Update(long deltaTime, SDL_Surface * buffer)
{
	this->setAng(this->ang);
	float zoom = 1 + this->sin_t[int(this->ang)%LOOKUP_SIZE_SIN];
	this->setZoom(zoom);
	this->RotoZoom(buffer, this->texture, this->ang, this->zoom, this->cos_t, this->sin_t);
	this->ang += 1;
}

CRotozoom::CRotozoom()
{
}


CRotozoom::~CRotozoom()
{
}

void CRotozoom::RotoZoom(SDL_Surface *buffer, SDL_Surface *texture, float ang, float zoom, long double *cos_t, long double *sin_t)
{
	int H = buffer->h;
	int W = buffer->w;

	int HTex = texture->h;
	int WTex = texture->w;
	unsigned int *pixelsBuffer = (unsigned int *)buffer->pixels;
	unsigned int *pixelTex = (unsigned int *)texture->pixels;



	int midW = W / 2;
	int midH = H / 2;
	for (int y = 0; y < H; y++)
		for (int x = 0; x < W; x++)
		{

			int u = (x - midW) * cos_t[int(ang) % LOOKUP_SIZE_SIN] + (y - midH) * (-sin_t[int(ang) % LOOKUP_SIZE_SIN]);
			int v = (x - midW) * sin_t[int(ang) % LOOKUP_SIZE_SIN] + (y - midH) * cos_t[int(ang) % LOOKUP_SIZE_SIN];

			u = (u)* zoom;
			v = (v)* zoom;
			u += 32 + midW;
			v += 32 + midH;
			u = abs(u % WTex);
			v = abs(v % HTex);
			unsigned int color = pixelTex[u + WTex * v];
			pixelsBuffer[x + W * y] = color;

		}
}
