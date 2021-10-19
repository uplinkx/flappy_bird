/***************************************************************************
 * FILENAME:    SDLX_utilsX.c
 * DESCRIPTION: File for powerful X utility functions that work like magic.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 25Jul2021
***************************************************************************/

#include "SDLX.h"

void SDLX_xIter(void *base, size_t nel, size_t width, void (*apply_fn)(void *))
{
	size_t	ix;

	ix = 0;
	SDL_assert(width != 0);
	while (ix < nel)
	{
		apply_fn(base);
		base = base + width;
		ix++;
	}
}

void	*SDLX_xLowest(void *base, size_t nel, size_t width, int (cmp)(const void *, const void *))
{
	size_t	curr;
	void	*result, *ptr;

	curr = 1; result = base; ptr = base + width;
	while (curr < nel) {
		if (cmp(ptr, result) < 0) result = ptr;
		ptr += width; curr++;
	}
	return (result);
}

void	*SDLX_xHighest(void *base, size_t nel, size_t width, int (cmp)(const void *, const void *))
{
	size_t	curr;
	void	*result, *ptr;

	curr = 1; result = base; ptr = base + width;
	while (curr < nel) {
		if (cmp(ptr, result) >= 0) result = ptr;
		ptr += width; curr++;
	}
	return (result);
}

void	*SDLX_xFirst(void *base, size_t nel, size_t width, SDL_bool (key_fn)(const void *))
{
	size_t	curr;
	void	*ptr;

	curr = 0;
	ptr = base;
	while (curr < nel) {
		if (key_fn(ptr)) { return (ptr); }
		ptr += width;
		curr++;
	}
	return (NULL);
}

void	*SDLX_xLast(void *base, size_t nel, size_t width, SDL_bool (key_fn)(const void *))
{
	size_t	curr;
	void	*ptr;

	curr = 0;
	ptr = base + (width * nel);
	while (curr < nel) {
		if (key_fn(ptr)) { return (ptr); }
		ptr -= width;
		curr++;
	}
	return (NULL);
}