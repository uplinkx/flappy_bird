/***************************************************************************
 * FILENAME:    button.c
 * DESCRIPTION: File that has the button functionality
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 19Oct2021
***************************************************************************/

#include "main.h"

void	*button_trigger_scene_switch(SDLX_button *self, void *vp_context, SDL_UNUSED size_t length)
{
	t_game_context *context;

	if (SDLX_GAME_RELEASE(g_GameInput, g_GameInput_prev, primleft))
	{
		context = vp_context;
		context->init_fn = self->meta1;
		context->shouldChange = SDL_TRUE;
	}

	return (NULL);
}