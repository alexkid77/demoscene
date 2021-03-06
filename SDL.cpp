// SDL.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//


#include "SDL.h"
#include "SDL_image.h"
#include "utils.h"
#include <stdio.h>
#include <string>
#include "CRotozoom.h"


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

	SDL_Surface *texture = SDL_CreateRGBSurface(0, 64, 64, 32,
		0, 0, 0, 0);









	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		const char *s = IMG_GetError();
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());

	}

	texture = loadSurface("textura.png", texture);




	

	CRotozoom rotozoom;
	rotozoom.Init(texture);
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
					buffer = SDL_CreateRGBSurface(0, width, height, 32,
						0, 0, 0, 0);

				}
			}
			if (event.type == SDL_MOUSEMOTION)
			{
				
			}
		}

	
	

	

	//	SDL_BlitSurface(buffer, NULL, bufferLens, NULL);

	
		
		
		
		rotozoom.Update(0, buffer);
		SDL_BlitSurface(buffer, NULL, screen, NULL);

		SDL_UpdateWindowSurface(window);
	
		t = t + 1;
	}



}



