/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 20:09:41 by home              #+#    #+#             */
/*   Updated: 2021/10/19 01:00:14 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#define PIPE_GAP (256)
#define HALF_GAP (PIPE_GAP / 2)

void	draw_pipe(t_pipes *pipes, t_pipe pipe)
{
	SDL_Rect	top_dest;
	SDL_Rect	bottom_dest;
	SDL_Renderer	*renderer;

	renderer = SDLX_GetDisplay()->renderer;
	top_dest.x = pipe.loc_x;
	top_dest.y = 0;
	top_dest.w = TILE_SIZE * DISPLAY_SCALE;
	top_dest.h = pipe.loc_y - (HALF_GAP);
	SDL_RenderCopy(renderer, pipes->pipe_texture, &(pipes->src_rect[PIPE_BODY]), &(top_dest));
	top_dest.y = top_dest.h;
	top_dest.h = TILE_SIZE * DISPLAY_SCALE;
	SDL_RenderCopy(renderer, pipes->pipe_texture, &(pipes->src_rect[PIPE_END]), &(top_dest));

	bottom_dest.x = pipe.loc_x;
	bottom_dest.y = pipe.loc_y + (HALF_GAP);
	bottom_dest.w = TILE_SIZE * DISPLAY_SCALE;
	bottom_dest.h = (WIN_HEIGHT) - bottom_dest.y;
	SDL_RenderCopy(renderer, pipes->pipe_texture, &(pipes->src_rect[PIPE_BODY]), &(bottom_dest));
	bottom_dest.y -= TILE_SIZE * DISPLAY_SCALE;
	bottom_dest.h = TILE_SIZE * DISPLAY_SCALE;
	SDL_RenderCopyEx(renderer, pipes->pipe_texture, &(pipes->src_rect[PIPE_END]), &(bottom_dest), 0, NULL, SDL_FLIP_VERTICAL);
}

void	draw_pipes(t_pipes *pipes)
{
	int		i;

	i = 0;
	while (i < pipes->pipe_capacity)
	{
		if (pipes->pipes[i].active == SDL_TRUE)
			draw_pipe(pipes, pipes->pipes[i]);
		i++;
	}
}

void	double_pipe_space(t_pipes *pipes)
{
	int		capacity;
	t_pipe	*temp;

	capacity = pipes->pipe_capacity;
	temp = malloc(sizeof(*temp) * (capacity * 2));
	bzero(temp, sizeof(*temp) * (capacity * 2));
	memcpy(temp, pipes->pipes, sizeof(*temp) * capacity);
	pipes->pipe_capacity *= 2;

	free(pipes->pipes);
	pipes->pipes = temp;
}

void	spawn_pipe(t_pipes *pipes)
{
	int		i;

	i = 0;
	while (i < pipes->pipe_capacity &&
			pipes->pipes[i].active == SDL_TRUE)
		i++;

	if (i == pipes->pipe_capacity)
		double_pipe_space(pipes);

	pipes->pipes[i].active = SDL_TRUE;
	pipes->pipes[i].loc_x = WIN_WIDTH;
	pipes->pipes[i].loc_y = (rand() % 10 + 5) * 25;

	pipes->current_pipe_amount++;
}

/*
** Change this later so that the pipe holds its collision mesh.
** and certain attributes are only calculated once.
*/

SDL_bool	collides_with_pipe(t_pipe pipe, int	player_loc_y)
{
	SDL_bool	result;
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
	player.y = player_loc_y;
	player.w = TILE_SIZE * DISPLAY_SCALE;
	player.h = TILE_SIZE * DISPLAY_SCALE;

	result = SDL_FALSE;
	result |= SDL_HasIntersection(&player, &top_pipe);
	result |= SDL_HasIntersection(&player, &bottom_pipe);
	return (result);
}

SDL_bool	pipe_collisions(t_pipes *pipes, int player_loc_y)
{
	int		i;

	i = 0;
	while (i < pipes->pipe_capacity)
	{
		if (pipes->pipes[i].active == SDL_TRUE)
		{
			if (collides_with_pipe(pipes->pipes[i], player_loc_y) == SDL_TRUE)
				return (SDL_TRUE);
		}
		i++;
	}
	return (SDL_FALSE);
}

void		update_active_pipes(t_pipes *pipes, int *score)
{
	int	i;

	i = 0;
	while (i < pipes->pipe_capacity)
	{
		if (pipes->pipes[i].active == SDL_TRUE)
		{
			pipes->pipes[i].loc_x -= 8;
			if (pipes->pipes[i].loc_x < -70 * 8)
			{
				pipes->pipes[i].active = SDL_FALSE;
				pipes->current_pipe_amount--;
			}
			if (pipes->pipes[i].loc_x == 40)
				(*score)++;
		}
		i++;
	}
}
