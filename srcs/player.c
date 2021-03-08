/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 20:55:48 by home              #+#    #+#             */
/*   Updated: 2021/03/07 16:35:45 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include <unistd.h>

void	draw_player(t_game_context *game_state, SDLX_Display *display)
{
	SDL_Rect	dest;
	double		angle;

	dest.h = TILE_SIZE * DISPLAY_SCALE;
	dest.w = TILE_SIZE * DISPLAY_SCALE;
	dest.x = 40;
	dest.y = game_state->player_loc_y;

	angle = (atan(game_state->player_vel_y * -1) * 180) / M_PI;
	angle *= .7;

	if (-1 < game_state->player_vel_y && game_state->ticks % 6 == 0)
		game_state->player_animation++;
	if (game_state->player_animation > FLAPPY_DOWN)
		game_state->player_animation = FLAPPY_UP;

	SDL_RenderCopyEx(display->renderer, game_state->texture, &(game_state->src_rect[game_state->player_animation]), &(dest), angle, NULL, SDL_FLIP_NONE);
	SDL_SetTextureColorMod(game_state->texture, 255, 255, 255);
}
