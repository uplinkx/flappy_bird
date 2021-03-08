/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 02:38:32 by home              #+#    #+#             */
/*   Updated: 2021/01/18 23:05:03 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <math.h>

# include <SDL_image.h>

# include "SDLX.h"

# include "structs.h"
# include "texture_id.h"

void		SDLU_start(SDLX_Display *dest);
void		SDLU_close(SDLX_Display *display);

SDL_Rect	*carve_flappy_bird_texture(void);

void		game_context_initialize(t_game_context *game_state, SDLX_Display *display);

// void		process_user_input(t_game_context *game_state);
void		process_user_input(t_game_context *game_state, SDLX_Display *display);
void		update_game_state(t_game_context *game_state);

void		pipe_collisions(t_game_context *game_state);

void		spawn_pipe(t_game_context *game_state);

void		draw_pipes(t_game_context *game_state, SDLX_Display *display);
void		draw_player(t_game_context *game_state, SDLX_Display *display);
void		draw_score(t_game_context *game_state, SDLX_Display *display);
void		draw_game_over(t_game_context *game_state, SDLX_Display *display);

void		itow(int n, SDL_Rect dest, SDLX_Display *dislay);

#endif
