#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef enum{false,true}bool;

bool Init();
bool loadImage();
SDL_Surface* loadSurface(char*);

SDL_Window* mWindow = NULL;
SDL_Surface* mSurface = NULL;
SDL_Surface* tPNGsurface = NULL;

SDL_Event eventControl;
int PollEventCheck = true;

int main()
{
	if(!Init())
	{
		fprintf(stderr, "Problem occured in Init() function !\n");
		return 1;
	}
	else
	{
		if(!loadImage())
		{
			fprintf(stderr, "Problem occured in loadImage() function !\n");
			return 1;
		}
		else
		{
			while(PollEventCheck)
			{
				while(SDL_PollEvent(&eventControl))
				{
					switch (eventControl.type)
					{
						case SDL_QUIT:
							PollEventCheck =false;
					}
				}
				SDL_BlitScaled( tPNGsurface,NULL, mSurface,NULL);
				SDL_UpdateWindowSurface(mWindow);
			}
		}
	}
	
	//Free loaded image
	SDL_FreeSurface( tPNGsurface );
	tPNGsurface = NULL;

	//Destroy window
	SDL_DestroyWindow( mWindow );
	mWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	
	return 0;
}
bool Init()
{
	bool success = true;
	if(SDL_Init(SDL_INIT_EVERYTHING)<0)
	{
		fprintf(stderr, "SDL could not initialize! SDL Error: %s\n",SDL_GetError() );
		success = false;
	}
	else
	{
		int imgFlags = IMG_INIT_PNG;

		if(!( IMG_Init( imgFlags ) & imgFlags ))
		{
			fprintf(stderr, "SDL_image could not initialize ! SDL_Image Error : %s\n",IMG_GetError());
			success = false;
		}
		else
		{
			mWindow = SDL_CreateWindow("SDL_Image",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				SDL_WINDOW_OPENGL);

			if( mWindow == NULL)
	 		{
	 			fprintf(stderr,"Window could not be created! SDL_Error: %s\n", SDL_GetError());
	 			success = false;
	 		}
	 		else
	 		{
				mSurface = SDL_GetWindowSurface(mWindow);
			}
		}
	}
	return success;
}
bool loadImage()
{
	bool success = true;
	tPNGsurface = loadSurface("loaded.png");
	if( tPNGsurface == NULL )
	{
		fprintf(stderr,"Failed to load PNG image!\n");
		success = false;
	}
	return success;
}
SDL_Surface* loadSurface(char* imageTitle)
{
	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* loadedSurface = IMG_Load(imageTitle);

	if(loadedSurface == NULL)
	{
		fprintf(stderr, "Unable to load image ! SDL_image Error : %s\n",IMG_GetError());
	}
	else
	{
		optimizedSurface = SDL_ConvertSurface(loadedSurface , mSurface->format ,0);

		if(optimizedSurface == NULL)
		{
			fprintf(stderr, "Unable to optimize image ! SDL Error: %s\n",SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}