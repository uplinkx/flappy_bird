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

# include <SDL2/SDL_image.h>

# include "SDLX.h"

# include "structs.h"
# include "texture_id.h"

# define TILE_SIZE	(16)

# define TILE (1)

void		SDLU_start(SDLX_Display *dest);
void		SDLU_close(SDLX_Display *display);

SDL_Rect	*carve_flappy_bird_texture(void);

void		game_context_initialize(t_game_context *game_state);

void		process_user_input(t_scene *game_state);
void		update_game_state(t_scene *game_state);

SDL_bool	pipe_collisions(t_pipes *pipes, int player_loc_y);

void		spawn_pipe(t_pipes *pipes);
void		update_active_pipes(t_pipes *pipes, int *score);

void		draw_background(t_scene *game_state, SDLX_Display *display);
void		draw_pipes(t_pipes *pipes);
void		draw_player(t_scene *game_state, SDLX_Display *display);
void		draw_score(t_scene *game_state, SDLX_Display *display);
void		draw_game_over(t_scene *game_state, SDLX_Display *display);

void		itow(int n, SDL_Rect dest, SDLX_Display *dislay);

void	*new_scene(size_t size, t_game_context *context, char *background_path, void *(close)(t_game_context *, void *), void *(update)(t_game_context *, void *));

void	*level_select_init(t_game_context *context, void *vp_scene);
void	*level_select_close(t_game_context *context, void *vp_scene);
void	*level_select_update(t_game_context *context, void *vp_scene);

void	*main_menu_select_init(t_game_context *context, void *vp_scene);
void	*main_menu_select_close(t_game_context *context, void *vp_scene);
void	*main_menu_select_update(t_game_context *context, void *vp_scene);

void	*death_scene_select_init(t_game_context *context, void *vp_scene);
void	*death_scene_select_close(t_game_context *context, void *vp_scene);
void	*death_scene_select_update(t_game_context *context, void *vp_scene);

int		fetch_button_sprite(SDLX_Sprite_Data **dst, int no);
void	*button_trigger_scene_switch(SDLX_button *self, void *vp_context, SDL_UNUSED size_t length);

#endif
