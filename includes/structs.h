/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 03:05:42 by home              #+#    #+#             */
/*   Updated: 2021/10/18 23:20:21 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct	s_pipe
{
	bool		active;
	int			loc_x;
	int			loc_y;
}				t_pipe;

struct s_game_context;
typedef void *(t_scene_fn)(struct s_game_context *, void *);

typedef struct	s_game_context
{
	bool		active;

	int			ticks;
	int			hiscore;

	bool		game_over;

	SDLX_Sprite	background;
	SDL_Texture	*capture_texture;

	SDL_bool	shouldQuit;
	SDL_bool	shouldChange;

	void		*meta;

	t_scene_fn	*init_fn;
	t_scene_fn	*update_fn;
	t_scene_fn	*close_fn;
}				t_game_context;

typedef struct	s_pipes
{
	SDL_Texture	*pipe_texture;
	SDL_Rect	*src_rect;

	int			pipe_capacity;
	int			current_pipe_amount;
	t_pipe		*pipes;
}				t_pipes;

typedef struct	s_scene
{
	SDL_Texture	*texture;
	SDL_Rect	*src_rect;

	SDL_Texture	*background;

	int			*ticks;
	int			score;

	bool		game_over;

	t_pipes		pipes;

	int			player_animation;
	int			player_loc_y;
	int			player_vel_y;
}				t_scene;

#endif
