/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 02:38:19 by home              #+#    #+#             */
/*   Updated: 2021/03/07 16:17:07 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_score(t_game_context *game_state, SDLX_Display *display)
{
	SDL_Rect	dest;

	dest.h = 5 * 4;
	dest.w = 4 * 4;
	dest.x = 400;
	dest.y = 48;
	itow(game_state->ticks, dest, display);
}

void	draw_game_over(t_game_context *game_state, SDLX_Display *display)
{
	SDL_Rect	dest;

	dest.h = TILE_SIZE * 4;
	dest.w = TILE_SIZE * 4;
	dest.x = (WIN_WIDTH) / 2 - (dest.h / 2);
	dest.y = (WIN_HEIGHT) / 2 - (dest.w / 2);
	SDL_RenderCopy(display->renderer, game_state->texture, &(game_state->src_rect[GAME_OVER]), &dest);
}
