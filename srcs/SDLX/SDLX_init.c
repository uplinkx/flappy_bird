/***************************************************************************
 * FILENAME:    SDLX_init.c
 * DESCRIPTION: Starts up SDLX and SDL. Does this automatically if
 * SDLX_getDislay() is called.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 22Jun2021
***************************************************************************/

#include "SDLX.h"

SDLX_GameInput	g_GameInput;
SDLX_GameInput	g_GameInput_prev;

void	SDLX_Start(SDLX_Display *dest)
{
	SDL_Window	*window;

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(
				WIN_TITLE,
				WIN_POS_X, WIN_POS_Y,
				WIN_WIDTH, WIN_HEIGHT,
				SDL_WINDOW_SHOWN
	);
	dest->window = window;
	dest->renderer = SDL_CreateRenderer(window, -1, 0);

	SDLX_RenderQueue_Init(&(default_RenderQueue));
	SDLX_CollisionBucket_Init(&(default_CollisionBucket), 0);

	atexit(SDLX_Close);
}

void	SDLX_Close(void)
{
	SDL_DestroyWindow(SDLX_GetDisplay()->window);
	SDL_free(default_CollisionBucket.content);
	SDL_free(default_RenderQueue.content);
	SDL_Log("Clean Exit");
	SDL_Quit();
}

SDLX_Display	*SDLX_GetDisplay(void)
{
	static SDLX_Display	display;

	if (display.window == NULL)
		SDLX_Start(&display);

	return (&display);
}
