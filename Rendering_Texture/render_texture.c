#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef enum{false , true}bool;


bool init();
bool loadMedia();
SDL_Texture* loadTexture(char*);

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

int main(int argc, char* args[] )
{
	if(!init())
	{
		fprintf(stderr, "Problem Occured !\n");
	}
	else
	{
		if(!loadMedia())
		{
			fprintf(stderr, "Problem Occured ! \n");
		}
		else
		{
			int PollEventCheck = true;
			SDL_Event event;

			while(PollEventCheck)
			{
				while(SDL_PollEvent(&event))
				{
					switch(event.type)
					{
						case SDL_QUIT:
						PollEventCheck = false;
						break;
					}
				}

				SDL_RenderClear(gRenderer);
				SDL_RenderCopy(gRenderer,
					gTexture,
					NULL,
					NULL);
				
				SDL_RenderPresent(gRenderer);
			}

		}
	}

	//Free loaded image
    SDL_DestroyTexture( gTexture );
    gTexture = NULL;

    //Destroy window    
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();

	return 0;	
}
bool init()
{
	bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO < 0) )
 	{
 		fprintf(stderr,"SDL could not initialize! SDL_Error: %s\n",SDL_GetError());
 		success = false;
 	}
 	else
 	{
		gWindow = SDL_CreateWindow("SDL_Rendering_Texture",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_OPENGL);

		if( gWindow == NULL)
		{
			fprintf(stderr, "Window could not be created ! SDL Error : %s\n",SDL_GetError() );
			success =false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow,
				-1,
				SDL_RENDERER_ACCELERATED);

			if(gRenderer == NULL)
			{
				fprintf(stderr, "Renderer could not be initialized ! SDL Error : %s\n",SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer,
					0,
					255,
					0,
					255);

				int imgFlags = IMG_INIT_PNG;

				if(!IMG_Init(imgFlags) & imgFlags)
				{
					fprintf(stderr, "SDL could not initialize ! SDL Error : %s\n",SDL_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}
SDL_Texture* loadTexture(char* imgTitle)
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(imgTitle);

	if(loadedSurface == NULL)
	{
		fprintf(stderr, "Image could not be loaded ! IMG Error : %s\n",IMG_GetError() );
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(gRenderer,loadedSurface);
		if(newTexture == NULL)
		{
			fprintf(stderr,"Unable to create texture from %s! SDL Error: %s\n", imgTitle, SDL_GetError() );
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}
bool loadMedia()
{
	bool success = true;
	gTexture = loadTexture("texture.png");
	
	if(gTexture == NULL)
	{
		fprintf(stderr, "Failed to load texture image !");
		success = false;
	}
	return success;
}