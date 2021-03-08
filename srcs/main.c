/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 02:31:10 by home              #+#    #+#             */
/*   Updated: 2021/03/07 16:28:54 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <emscripten.h>
#include <time.h>

void	game_context_initialize(t_game_context *game_state, SDLX_Display *display)
{
	game_state->active = true;

	game_state->texture = IMG_LoadTexture(display->renderer, "resources/flappy_bird.png");
	game_state->src_rect = carve_flappy_bird_texture();

	game_state->ticks = 0;
	game_state->game_over = false;

	game_state->pipe_capacity = 10;
	game_state->current_pipe_amount = 0;

	game_state->pipes = malloc(sizeof(*(game_state->pipes)) * (10));
	bzero(game_state->pipes, sizeof(*(game_state->pipes)) * (10));

	game_state->player_animation = FLAPPY_MID;
	game_state->player_vel_y = 0;
	game_state->player_loc_y = 100;

	srand(time(NULL));
}

void	main_loop(void *v_cxt)
{
	SDLX_Display	*display;
	t_game_context	*cxt;

	cxt = v_cxt;
	display = SDLX_GetDisplay();
	process_user_input(cxt, display);

	update_game_state(cxt);

	draw_pipes(cxt, display);
	draw_player(cxt, display);
	draw_score(cxt, display);

	if (cxt->game_over == true)
		game_context_initialize(cxt, display);
		// draw_game_over(cxt, display);

	SDL_RenderPresent(display->renderer);
	SDL_RenderClear(display->renderer);
}

int	main(void)
{
	SDLX_Display	*display;
	t_game_context	cxt;

	display = SDLX_GetDisplay();
	game_context_initialize(&cxt, display);
	emscripten_set_main_loop_arg(main_loop, (void *)&(cxt), 0, SDL_TRUE);
	return (0);
}
