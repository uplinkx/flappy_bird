/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 20:52:34 by home              #+#    #+#             */
/*   Updated: 2021/03/12 16:51:10 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		update_active_pipes(t_game_context *game_state)
{
	int	i;

	i = 0;
	while (i < game_state->pipe_capacity)
	{
		if (game_state->pipes[i].active == true)
		{
			game_state->pipes[i].loc_x -= 2;
			if (game_state->pipes[i].loc_x < -70)
			{
				game_state->pipes[i].active = false;
				game_state->current_pipe_amount--;
			}
			if (game_state->pipes[i].loc_x == 30)
				game_state->score++;
		}
		i++;
	}
}

#include <unistd.h>

void		update_game_state(t_game_context *game_state)
{
	if (game_state->ticks % 175 == 0)
		spawn_pipe(game_state);
	update_active_pipes(game_state);


	if (game_state->ticks % 4 == 0)
		game_state->player_loc_y -= game_state->player_vel_y;
	if (game_state->player_vel_y > -10 && game_state->ticks % 8 == 0)
		game_state->player_vel_y += -1;

	pipe_collisions(game_state);

	game_state->ticks++;
	usleep(10000);
}
