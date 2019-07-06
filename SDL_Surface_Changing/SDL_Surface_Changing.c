#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef enum {false,true}bool;

enum Button_Type{
SDL_Pressed_Default,
SDL_Pressed_Up,
SDL_Pressed_Down,
SDL_Pressed_Right,
SDL_Pressed_Left,
SDL_Pressed_Total,
};

SDL_Window *window = NULL;
SDL_Surface* keyPressedSurface[SDL_Pressed_Total];
SDL_Surface* currentSurface = NULL;
SDL_Surface* mainSurface = NULL;

SDL_Event currentEvent;

bool init();
bool loadMedia();
SDL_Surface* loadSurface(char*);
void close();


int main()
{
bool quit = false;

if(! init())
{
	fprintf(stderr,"SDL could not initialize SDL_Init Function ! SDL_Error : %s\n",SDL_GetError());
}
else
{
	if(!loadMedia())
	{
		fprintf(stderr, "Error ocured loadMedia in main ! SDL_Error : %s\n",SDL_GetError());
		return 1;
	}
	else
	{
		while(!quit)
		{
			while(SDL_PollEvent(&currentEvent))
			{
				if(currentEvent.type == SDL_QUIT)
				{
					quit = true;
				}
				else if(currentEvent.type == SDL_KEYDOWN)
				{
					switch( currentEvent.key.keysym.sym )
					{
						case SDLK_UP:
						currentSurface = keyPressedSurface[SDL_Pressed_Up];
						break;
						case SDLK_DOWN:
						currentSurface = keyPressedSurface[SDL_Pressed_Down];
						break;
						case SDLK_RIGHT:
						currentSurface = keyPressedSurface[SDL_Pressed_Right];
						break;
						case SDLK_LEFT:
						currentSurface = keyPressedSurface[SDL_Pressed_Left];
						break;
						default:
						currentSurface = keyPressedSurface[SDL_Pressed_Default];
						break;
					}
				}

				SDL_BlitSurface(currentSurface,
						NULL,
						mainSurface,
						NULL);

			
				SDL_UpdateWindowSurface(window);
			}
		}
	}
}

for(int i = 0 ; i < SDL_Pressed_Total ; ++i)
{
	SDL_FreeSurface(keyPressedSurface[i]);

	keyPressedSurface[i] = NULL;
}

SDL_DestroyWindow(window);
window = NULL;

SDL_Quit();
return 0;
}

bool init()
{
bool success = true;

if(SDL_Init(SDL_INIT_EVERYTHING)<0)
{
	fprintf(stderr,"SDL could not initialize SDL_Init Function ! SDL_Error : %s\n",SDL_GetError());
	success = false;
}
else
{
	window = SDL_CreateWindow("SDL_Ex",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL);

	if( window == NULL)
	{
		fprintf(stderr,"Window could not be created ! SDL_Error : %s\n",SDL_GetError());
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
bool success = true;

char* default_title = "press.bmp";
char* up = "up.bmp";
char* down = "down.bmp";
char* right = "right.bmp";
char* left = "left.bmp";

keyPressedSurface[SDL_Pressed_Default] = loadSurface(default_title);
if(keyPressedSurface[SDL_Pressed_Default] == NULL)
{
	fprintf(stderr, "Error ! Loading Default Surface ! SDL_Error : %s\n",SDL_GetError());
	success = false;
}

keyPressedSurface[SDL_Pressed_Up] = loadSurface(up);
if(keyPressedSurface[SDL_Pressed_Up] == NULL)
{
	fprintf(stderr, "Error ! Loading Up Surface ! SDL_Error : %s\n",SDL_GetError());
	success = false;
}

keyPressedSurface[SDL_Pressed_Down] = loadSurface(down);
if(keyPressedSurface[SDL_Pressed_Down] == NULL)
{
	fprintf(stderr, "Error ! Loading Down Surface ! SDL_Error : %s\n",SDL_GetError());
	success = false;
}

keyPressedSurface[SDL_Pressed_Right] = loadSurface(right);
if(keyPressedSurface[SDL_Pressed_Right] == NULL)
{
	fprintf(stderr, "Error ! Loading Right Surface ! SDL_Error : %s\n",SDL_GetError());
	success = false;
}

keyPressedSurface[SDL_Pressed_Left] = loadSurface(left);
if(keyPressedSurface[SDL_Pressed_Left] == NULL)
{
	fprintf(stderr, "Error ! Loading Left Surface ! SDL_Error : %s\n",SDL_GetError());
	success = false;
}

return success;
}
SDL_Surface* loadSurface(char* imagePath)
{

	SDL_Surface *loadSurface = SDL_LoadBMP(imagePath);

	if(loadSurface == NULL)
	{
		fprintf(stderr, "Error Occured during loading the surface ! SDL_Error : %s\n",SDL_GetError());
	}

	return loadSurface;
}