// SDL.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//


#include "SDL.h"
#include "SDL_image.h"
#include "utils.h"
#include <stdio.h>
#include <string>
#include "IEffect.h"
#include "CLensEffect.h"



int main(int argc, char* argv[])
{


	SDL_Init(SDL_INIT_VIDEO);
	SDL_PixelFormat *fmt;
	SDL_Window * window = SDL_CreateWindow("",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 480,
		SDL_WINDOW_RESIZABLE);

	SDL_Surface * screen = SDL_GetWindowSurface(window);


	fmt = screen->format;
	const char* surfacePixelFormatName = SDL_GetPixelFormatName(screen->format->format);
	int width = screen->w;
	int height = screen->h;


	SDL_Surface *buffer = SDL_CreateRGBSurface(0, width, height, 32,
		0, 0, 0, 0);


	unsigned int * pixels = (unsigned int *)buffer->pixels;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{

			pixels[x + y * width] = SDL_MapRGBA(screen->format, 255, x^y, x ^ (y + x), 255);
		}
	}

	buffer = loadSurface("prueba.png", buffer);






	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		const char *s = IMG_GetError();
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());

	}

	
	IEffect *fx1=new CLensEffect (100.00, 130, 70);
	IEffect *fx2 = new CLensEffect(80.0, 80, 70);
	CLensEffect *lente =(CLensEffect*) fx1;
	CLensEffect *lente2 = (CLensEffect*)fx2;
	//CLensEffect lente(100.00, 130, 70);
	//CLensEffect lente2(80.0, 80, 70);
	
	
	lente->Init(buffer);
	lente2->Init(buffer);
	lente->x = buffer->w / 2;
	lente->y = buffer->h / 2;
	lente2->x = 70;
	lente2->y = 70;


	float t = 0;

	while (1)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) exit(0);
			if (event.type == SDL_WINDOWEVENT)
			{
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					screen = SDL_GetWindowSurface(window);
					//pixels = (unsigned int *)screen->pixels;
					width = screen->w;
					height = screen->h;

				}
			}
			if (event.type == SDL_MOUSEMOTION)
			{
				lente->y= event.motion.y;
				lente->x = event.motion.x;
			}
		}

		//lente->y = buffer->h / 2 + (90 + sin(t) * 10) * cos(t);
		//lente->x = buffer->h / 2 + 90 * sin(t);
		lente2->x = 90 + 90 * cos(t);
		lente2->y = 90 + 90 * sin(t);
	

		SDL_Surface *bufferLens = SDL_CreateRGBSurface(0, width, height, 32,
			0, 0, 0, 0);



		if (bufferLens == NULL) {
			const char *s = SDL_GetError();
			SDL_Log("SDL_CreateRGBSurface() failed: %s", s);
			exit(1);
		}
		SDL_BlitSurface(buffer, NULL, bufferLens, NULL);

		lente->Update(t, bufferLens);
		lente2->Update(t, bufferLens);
		

		t += 0.01;
		SDL_BlitSurface(bufferLens, NULL, screen, NULL);

		SDL_UpdateWindowSurface(window);
		SDL_FreeSurface(bufferLens);

	}

	delete lente;
	delete lente2;

}

