/***************************************************************************
 * FILENAME:    SDLX_fps.c
 * DESCRIPTION: Functions to make app run at a consitsent frame rate.
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 29Jan2021
***************************************************************************/

#include "SDLX_ticks.h"
#include "SDLX.h"

#define RENDER_TIME (2)

int		 SDLX_discrete_frames(int *ticks)
{
	static Uint32	last_timestamp;
	Uint32			resume_time;
	int				result;

	result = EXIT_SUCCESS;
	resume_time = last_timestamp + TICK_RATE;

	if (ticks != NULL)
		(*ticks)++;

	if (resume_time >= SDL_GetTicks() + RENDER_TIME)
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), resume_time));
	else
	{
		SDL_Log("Frame exceeded the rate of consistent gameplay, could not take a rest");
		SDLX_RenderQueue_Skip(NULL, NULL);
		result = EXIT_FAILURE;
	}

	// SDL_Log("[Frame]");

	last_timestamp = SDL_GetTicks();
	return (result);
}
