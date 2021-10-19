/***************************************************************************
 * FILENAME:    SDLX_utils.c
 * DESCRIPTION: Utility Functions that don't have a specific file.
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 08Feb2021
***************************************************************************/

#include "SDLX.h"

SDLX_direction	SDLX_reverse_dir(SDLX_direction direction)
{
	direction.c.x *= -1;
	direction.c.y *= -1;

	return (direction);
}

SDLX_Sprite		*SDLX_new_Sprite(SDLX_Sprite *dst)
{
	if (dst == NULL)
		return (dst);

	dst->current = 0;

	dst->dst = &(dst->_dst);
	dst->angle = 0;
	dst->center = NULL;
	dst->flip = SDL_FLIP_NONE;

	return (dst);
}

void			SDLX_Mouse_to_Screen(int *x, int *y)
{
	(*x) /= DISPLAY_SCALE;
	(*y) /= DISPLAY_SCALE;
}

# define SDLX_LRED	"\033[31m"

SDL_Texture		*SDLX_LoadTexture(char *path)
{
	SDL_Texture	*res;

	res = IMG_LoadTexture(SDLX_GetDisplay()->renderer, path);
	if (res == NULL)
		SDL_Log(SDLX_LRED"Did not load texture from file: %s", path);

	return (res);
}

SDLX_Sprite		SDLX_Sprite_Static(char *path)
{
	SDLX_Sprite	res;

	SDLX_new_Sprite(&(res));
	res.sprite_data = SDL_calloc(1, sizeof(*(res.sprite_data)));
	res.sprite_data->texture = SDLX_LoadTexture(path);
	res.sprite_data[0].src = NULL;
	res.sprite_data[0].cycle = 1;

	res.dst = NULL;

	return (res);
}

double	SDLX_Degree_to_Radian(double degree) { return (degree * M_PI / 180 ); }
double	SDLX_Radian_to_Degree(double degree) { return (degree * 180 / M_PI + 90); }