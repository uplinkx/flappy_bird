/***************************************************************************
 * FILENAME:    SDLX_render.c
 * DESCRIPTION: Utility functions for rendering the screen.
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 24Jan2021
***************************************************************************/

#include "SDLX.h"

// The function below will be called at the end of each draw stage
// and display the renderer onto the window, and prep it for a new
// draw stage.

void	SDLX_ScreenReset(SDL_Renderer *renderer, SDL_Color *bg_color)
{
	// SDL_Log("NEW FRAME DRAWN");

	SDL_RenderPresent(renderer);
	if (bg_color != NULL)
		SDL_SetRenderDrawColor(renderer, bg_color->r, bg_color->g, bg_color->b, bg_color->a);
	// else
	// 	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	SDL_RenderClear(renderer);

	SDLX_Sprite	*background;

	background = SDLX_GetBackground();
	if (background != NULL)
		SDLX_DrawAnimation(renderer, background);

	// Line below might be unecessary.
	// SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

SDL_Texture	*SDLX_CaptureScreen(SDLX_RenderQueue **Queues, size_t amount, SDL_bool reverse)
{
	size_t	i;
	size_t	render_object_amount;
	SDL_Texture	*result;
	SDL_Texture	*save;

	result = SDL_CreateTexture(SDLX_GetDisplay()->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIN_WIDTH, WIN_HEIGHT);

	save = NULL;
	save = SDL_GetRenderTarget(SDLX_GetDisplay()->renderer);

	SDL_SetRenderTarget(SDLX_GetDisplay()->renderer, result);
	SDL_RenderClear(SDLX_GetDisplay()->renderer);

	SDLX_DrawAnimation(SDLX_GetDisplay()->renderer, SDLX_GetBackground());

	render_object_amount = default_RenderQueue.index;
	SDLX_RenderQueue_Flush(NULL, NULL, reverse);
	default_RenderQueue.index = render_object_amount;

	i = 0;
	while (i < amount)
	{
		render_object_amount = Queues[i]->index;
		SDLX_RenderQueue_Flush(Queues[i], NULL, reverse);
		Queues[i]->index = render_object_amount;
		i++;
	}

	SDL_SetRenderTarget(SDLX_GetDisplay()->renderer, save);

	return (result);
}