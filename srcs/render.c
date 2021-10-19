/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 02:38:19 by home              #+#    #+#             */
/*   Updated: 2021/10/18 23:10:30 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_score(t_scene *game_state, SDLX_Display *display)
{
	SDL_Rect	dest;

	dest.h = 5 * DISPLAY_SCALE;
	dest.w = 4 * DISPLAY_SCALE;
	dest.x = 400;
	dest.y = 48;
	itow(game_state->score, dest, display);
}

void	draw_game_over(t_scene *game_state, SDLX_Display *display)
{
	SDL_Rect	dest;

	dest.h = TILE_SIZE * 4 * DISPLAY_SCALE;
	dest.w = TILE_SIZE * 4 * DISPLAY_SCALE;
	dest.x = (WIN_WIDTH) / 2 - (dest.h / 2);
	dest.y = (WIN_HEIGHT) / 2 - (dest.w / 2);
	SDL_RenderCopy(display->renderer, game_state->texture, &(game_state->src_rect[GAME_OVER]), &dest);
}

void	draw_background(t_scene *game_state, SDLX_Display *display)
{
	SDL_Rect dest;

	int x = *(game_state->ticks);
	x %= WIN_WIDTH;
	x -= WIN_WIDTH;
	x *= -1;

	dest.h = WIN_HEIGHT;
	dest.w = WIN_WIDTH;
	dest.y = 0;
	dest.x = x;
	SDL_RenderCopyEx(display->renderer, game_state->background, NULL, &(dest), 0, NULL, SDL_FLIP_NONE);
	dest.x -= WIN_WIDTH;
	SDL_RenderCopyEx(display->renderer, game_state->background, NULL, &(dest), 0, NULL, SDL_FLIP_NONE);
}

