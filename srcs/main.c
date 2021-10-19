/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 02:31:10 by home              #+#    #+#             */
/*   Updated: 2021/10/18 21:44:13 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <time.h>

#ifdef EMCC
 # include <emscripten.h>
#endif

void	game_context_initialize(t_game_context *game_state, SDLX_Display *display)
{
	game_state->active = true;

	game_state->texture = IMG_LoadTexture(display->renderer, "resources/flappy_bird.png");
	game_state->background = IMG_LoadTexture(display->renderer, "resources/flappy_background.png");
	game_state->src_rect = carve_flappy_bird_texture();

	game_state->ticks = 0;
	game_state->score = 0;
	game_state->game_over = false;

	game_state->pipe_capacity = 10;
	game_state->current_pipe_amount = 0;

	game_state->pipes = malloc(sizeof(*(game_state->pipes)) * (10));
	bzero(game_state->pipes, sizeof(*(game_state->pipes)) * (10));

	game_state->player_animation = FLAPPY_MID;
	game_state->player_vel_y = 0;
	game_state->player_loc_y = 100;

	game_state->shouldQuit = SDL_FALSE;

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

	draw_background(cxt, display);

	draw_pipes(cxt, display);
	draw_player(cxt, display);
	draw_score(cxt, display);

	cxt->shouldQuit = SDLX_poll();

	if (cxt->game_over == true)
		game_context_initialize(cxt, display);
		// draw_game_over(cxt, display);

	SDL_RenderPresent(display->renderer);
	SDL_RenderClear(display->renderer);
}

// void	main_loop(void *context_addr)
// {
// 	t_game_context	*context;

// 	context = context_addr;
// 	// if (context->scene == SDL_FALSE)
// 	// {
// 	// 	context->init_fn(context, context->meta);
// 	// }

// 	context->shouldQuit = SDLX_poll();
// 	// SDLX_KeyMap(&(g_GameInput.key_mapper), g_GameInput.keystate);

// 	// SDLX_GameInput_Mouse_Fill(&(g_GameInput), SDL_TRUE);

// 	// context->update_fn(context, context->meta);

// 	draw_pipes(context, SDLX_GetDisplay());
// 	draw_player(context, SDLX_GetDisplay());
// 	draw_score(context, SDLX_GetDisplay());

// 	// if (context->shouldQuit != SDL_TRUE && SDLX_discrete_frames(&(context->ticks)) != EXIT_FAILURE)
// 	// {
// 	// 	SDLX_RenderQueue_Flush(NULL, NULL, SDL_TRUE);
// 	// 	SDLX_ScreenReset(SDLX_GetDisplay()->renderer, NULL);
// 	// }

// 	// SDLX_record_input(NULL);

// 	// if (context->scene == SDL_FALSE)
// 	// {
// 	// 	SDLX_CollisionBucket_Flush(NULL);
// 	// 	SDLX_RenderQueue_Flush(NULL, SDLX_GetDisplay()->renderer, SDL_FALSE);

// 	// 	context->close_fn(context, context->meta);
// 	// }
// }

int	main(void)
{
	SDLX_Display	*display;
	t_game_context	cxt;

	display = SDLX_GetDisplay();
	game_context_initialize(&cxt, display);
	#ifdef EMCC
		emscripten_set_main_loop_arg(main_loop, (void *)&(cxt), 0, SDL_TRUE);
	#else
		while (cxt.shouldQuit == SDL_FALSE)
			main_loop(&(cxt));
	#endif
	return (0);
}
