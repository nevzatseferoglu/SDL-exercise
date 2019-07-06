#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef enum{false,true}bool;

bool init();
bool loadMedia();
SDL_Surface* loadImage(char*);


//The window we'll be rendering to
SDL_Window* window = NULL;
	
//The surface contained by the window
SDL_Surface* mainSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* alteredSurface = NULL;

//To close the window
SDL_Event event;

int main()
{
	int Poll_EventControl = 0;

	if(! init())
	{
		printf("Failed to initialization !\n");
		return 1;
	}
	else
	{
		if(! loadMedia())
		{
			printf( "Failed to load media!\n" );
			return 1;
		}
		else
		{
			while(!Poll_EventControl)
			{
				while(SDL_PollEvent(&event))
				{
					switch (event.type)
					{
						case SDL_QUIT:
						Poll_EventControl = 1;
						break;
					}
				}

				SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = SCREEN_HEIGHT;

				SDL_BlitScaled( alteredSurface,NULL, mainSurface, &stretchRect );

				SDL_UpdateWindowSurface(window);
			}

		}
	}

	SDL_FreeSurface(mainSurface);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

bool init()
{
	bool success = true ;

 	if(SDL_Init(SDL_INIT_VIDEO < 0) )
 	{
 		fprintf(stderr,"SDL could not initialize! SDL_Error: %s\n",SDL_GetError());
 		success = false;
 	}
 	else
 	{
 		window = SDL_CreateWindow("SDL_Test",
 				SDL_WINDOWPOS_CENTERED,
 				SDL_WINDOWPOS_CENTERED,
 				SCREEN_WIDTH,
 				SCREEN_HEIGHT,
 				SDL_WINDOW_OPENGL);
 		if( window == NULL)
 		{
 			fprintf(stderr,"Window could not be created! SDL_Error: %s\n", SDL_GetError());
 			success = false;
 		}
 		else
 		{
 			mainSurface = SDL_GetWindowSurface(window);
 		}
 	}
 		return success;
}
bool loadMedia()
{
	int success = true;

	alteredSurface = loadImage("stretch.bmp");

	if(alteredSurface == NULL)
	{
		fprintf(stderr,"Unable to load image %s! SDL Error: %s\n","02_getting_an_image_on_the_screen/hello_world.bmp",SDL_GetError());
		success = false;
	}
	return success;
}
SDL_Surface* loadImage(char* imageTitle)
{
	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* loadedImageSurface = SDL_LoadBMP(imageTitle);

	if(loadedImageSurface == NULL)
	{
		fprintf(stderr, "Error occured during loading image ! SDL_Error : %s\n",SDL_GetError());
	}
	else
	{
		optimizedSurface = SDL_ConvertSurface(loadedImageSurface , mainSurface->format , 0);

		if(optimizedSurface == NULL)
		{
			fprintf(stderr, "Error occured during converting image ! SDL_Error : %s\n",SDL_GetError());
		}

		SDL_FreeSurface(loadedImageSurface);
	}

	return optimizedSurface;
}
