/***************************************************************************
 * FILENAME:    SDLX_math.c
 * DESCRIPTION: Common math functions.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 09Jul2021
***************************************************************************/

#include "SDLX.h"

SDL_Point	SDLX_RotatePoint(SDL_Point *point, double angle)
{
	SDL_Point	result;
	double		cos;
	double		sin;

	cos = SDL_cos(angle);
	sin = SDL_sin(angle);

	result.x = point->x * cos - point->y * sin;
	result.y = point->x * sin + point->y * cos;

	return (result);
}