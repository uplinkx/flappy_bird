/***************************************************************************
 * FILENAME:    sprite_buttons.c
 * DESCRIPTION: File that parses and returns the sprites for buttons
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

SDLX_Sprite_Data	*carve_button_sprite(void)
{
	size_t				ix;
	SDL_Texture			*texture;
	SDLX_Sprite_Data	*result;

	result = SDL_malloc(sizeof(*result) * 20);
	texture = SDLX_LoadTexture("resources/starto.png");

	ix = 0;
	while (ix < 10)
	{
		result[ix].texture = texture;
		result[ix]._src = (SDL_Rect){ix * 32, 0, 32, 16};
		result[ix].src = &(result[ix]._src);
		result[ix].cycle = 9;
		ix++;
	}

	while (ix < 20)
	{
		result[ix].texture = texture;
		result[ix]._src = (SDL_Rect){(ix - 10) * 32, 16, 32, 16};
		result[ix].src = &(result[ix]._src);
		result[ix].cycle = 9;
		ix++;
	}
	return (result);
}

int		fetch_button_sprite(SDLX_Sprite_Data **dst, int no)
{
	static SDLX_Sprite_Data	*sprite_arr;

	if (sprite_arr == NULL)
		sprite_arr = carve_button_sprite();

	if (no == 0)		{ (*dst) = &(sprite_arr[0]); return (EXIT_SUCCESS); }
	else if (no == 1)	{ (*dst) = &(sprite_arr[10]); return (EXIT_SUCCESS); }
	else { return (EXIT_FAILURE); }
}