/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 20:09:41 by home              #+#    #+#             */
/*   Updated: 2021/03/07 16:38:31 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#define PIPE_GAP (256)
#define HALF_GAP (PIPE_GAP / 2)

void	draw_pipe(t_game_context *game_state, SDLX_Display *display, t_pipe pipe)
{
	SDL_Rect	top_dest;
	SDL_Rect	bottom_dest;

	top_dest.x = pipe.loc_x;
	top_dest.y = 0;
	top_dest.w = TILE_SIZE * DISPLAY_SCALE;
	top_dest.h = pipe.loc_y - (HALF_GAP);
	SDL_RenderCopy(display->renderer, game_state->texture, &(game_state->src_rect[PIPE_BODY]), &(top_dest));
	top_dest.y = top_dest.h;
	top_dest.h = TILE_SIZE * DISPLAY_SCALE;
	SDL_RenderCopy(display->renderer, game_state->texture, &(game_state->src_rect[PIPE_END]), &(top_dest));

	bottom_dest.x = pipe.loc_x;
	bottom_dest.y = pipe.loc_y + (HALF_GAP);
	bottom_dest.w = TILE_SIZE * DISPLAY_SCALE;
	bottom_dest.h = (WIN_HEIGHT) - bottom_dest.y;
	SDL_RenderCopy(display->renderer, game_state->texture, &(game_state->src_rect[PIPE_BODY]), &(bottom_dest));
	bottom_dest.y -= TILE_SIZE * DISPLAY_SCALE;
	bottom_dest.h = TILE_SIZE * DISPLAY_SCALE;
	SDL_RenderCopyEx(display->renderer, game_state->texture, &(game_state->src_rect[PIPE_END]), &(bottom_dest), 0, NULL, SDL_FLIP_VERTICAL);
}

void	draw_pipes(t_game_context *game_state, SDLX_Display *display)
{
	int		i;
	t_pipe	*pipes;

	i = 0;
	pipes = game_state->pipes;
	while (i < game_state->pipe_capacity)
	{
		if (pipes[i].active == true)
			draw_pipe(game_state, display, pipes[i]);
		i++;
	}
}

void	double_pipe_space(t_game_context *game_state)
{
	int		capacity;
	t_pipe	*temp;

	capacity = game_state->pipe_capacity;
	temp = malloc(sizeof(*temp) * (capacity * 2));
	bzero(temp, sizeof(*temp) * (capacity * 2));
	memcpy(temp, game_state->pipes, sizeof(*temp) * capacity);
	game_state->pipe_capacity *= 2;

	free(game_state->pipes);
	game_state->pipes = temp;
}

void	spawn_pipe(t_game_context *game_state)
{
	int		i;

	i = 0;
	while (i < game_state->pipe_capacity &&
			game_state->pipes[i].active == true)
		i++;

	if (i == game_state->pipe_capacity)
		double_pipe_space(game_state);

	game_state->pipes[i].active = true;
	game_state->pipes[i].loc_x = WIN_WIDTH;
	game_state->pipes[i].loc_y = (rand() % 10 + 5) * 25;

	game_state->current_pipe_amount++;
}

/*
** Change this later so that the pipe holds its collision mesh.
** and certain attributes are only calculated once.
*/

bool	collides_with_pipe(t_pipe pipe, t_game_context *game_state)
{
	bool		result;
	SDL_Rect	top_pipe;
	SDL_Rect	bottom_pipe;

	SDL_Rect	player;

	top_pipe.x = pipe.loc_x;
	top_pipe.y = 0;
	top_pipe.w = TILE_SIZE * DISPLAY_SCALE;
	top_pipe.h = pipe.loc_y - (HALF_GAP);

	bottom_pipe.x = pipe.loc_x;
	bottom_pipe.y = pipe.loc_y + (HALF_GAP);
	bottom_pipe.w = TILE_SIZE * DISPLAY_SCALE;
	bottom_pipe.h = (WIN_HEIGHT) - bottom_pipe.y;

	player.x = 40;
	player.y = game_state->player_loc_y;
	player.w = TILE_SIZE * DISPLAY_SCALE;
	player.h = TILE_SIZE * DISPLAY_SCALE;

	result = false;
	result |= SDL_HasIntersection(&player, &top_pipe);
	result |= SDL_HasIntersection(&player, &bottom_pipe);
	return (result);
}

void	pipe_collisions(t_game_context *game_state)
{
	int		i;

	i = 0;
	while (i < game_state->pipe_capacity)
	{
		if (game_state->pipes[i].active == true)
		{
			if (collides_with_pipe(game_state->pipes[i], game_state) == true)
				game_state->game_over = true;
		}
		i++;
	}
}
