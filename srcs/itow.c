/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 21:58:31 by home              #+#    #+#             */
/*   Updated: 2021/03/07 16:17:07 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include "main.h"

SDL_Texture	*load_number_texture(SDL_Renderer *renderer)
{
	static SDL_Texture	*numbers_texture;

	if (numbers_texture == NULL)
		numbers_texture = IMG_LoadTexture(renderer, "resources/pixel_numbers_white.png");
	return (numbers_texture);
}

SDL_Rect	*number_scr_Rects(void)
{
	int				i;
	static SDL_Rect	*src_rects;

	if (src_rects == NULL)
	{
		src_rects = malloc(sizeof(*src_rects) * (12));

		i = 0;
		while (i < 12)
		{
			src_rects[i].h = 5;
			src_rects[i].w = 4;
			src_rects[i].x = 4 * i;
			src_rects[i].y = 0;
			i++;
		}
	}
	return (src_rects);
}

#define MINUS_SIGN	(10)
#define PLUS_SIGN	(11)

void		itow(int n, SDL_Rect dest, SDLX_Display *dislay)
{
	int			temp;
	bool		neg_sign;
	SDL_Texture	*numbers;
	SDL_Rect	*num_src;

	num_src = number_scr_Rects();
	numbers = load_number_texture(dislay->renderer);
	if (n == 0)
		SDL_RenderCopy(dislay->renderer, numbers, &num_src[0], &dest);

	neg_sign = false;
	if (n < 0)
		neg_sign = true;

	while (n != 0)
	{
		temp = n % 10;
		if (temp < 0)
			temp *= -1;
		SDL_RenderCopy(dislay->renderer, numbers, &num_src[temp], &dest);
		dest.x -= dest.w;
		n /= 10;
	}
	if (neg_sign == true)
		SDL_RenderCopy(dislay->renderer, numbers, &num_src[MINUS_SIGN], &dest);
}
