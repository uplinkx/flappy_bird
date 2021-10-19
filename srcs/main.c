/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 02:31:10 by home              #+#    #+#             */
/*   Updated: 2021/10/19 02:31:16 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <time.h>

#ifdef EMCC
 # include <emscripten.h>
#endif

void	game_context_initialize(t_game_context *game_state)
{
	game_state->active = SDL_TRUE;
	game_state->ticks = 0;
	game_state->score = 0;

	game_state->game_over = SDL_FALSE;
	game_state->shouldQuit = SDL_FALSE;
	game_state->shouldChange = SDL_TRUE;

	// game_state->init_fn = level_select_init;
	game_state->init_fn = main_menu_select_init;

	srand(time(NULL));
}

void	main_loop(void *context_addr)
{
	SDLX_Display	*display;
	t_game_context	*context;

	context = context_addr;
	display = SDLX_GetDisplay();
	context->shouldQuit = SDLX_poll();

	if (context->shouldChange == SDL_TRUE)
	{
		context->init_fn(context, context->meta);
		context->shouldChange = SDL_FALSE;
	}

	SDLX_KeyMap(&(g_GameInput.key_mapper), g_GameInput.keystate);
	SDLX_GameInput_Mouse_Fill(&(g_GameInput), SDL_TRUE);

	context->update_fn(context, context->meta);

	if (context->shouldQuit != SDL_TRUE && SDLX_discrete_frames(&(context->ticks)) != EXIT_FAILURE)
	{
		SDLX_RenderQueue_Flush(NULL, NULL, SDL_FALSE);
		SDLX_ScreenReset(SDLX_GetDisplay()->renderer, NULL);
	}

	SDLX_record_input(NULL);

	if (context->shouldChange == SDL_TRUE)
	{
		SDLX_CollisionBucket_Flush(NULL);
		SDLX_RenderQueue_Flush(NULL, SDLX_GetDisplay()->renderer, SDL_FALSE);

		context->close_fn(context, context->meta);
	}
}

int	main(void)
{
	SDLX_Display	*display;
	t_game_context	cxt;

	cxt.hiscore = 0;
	display = SDLX_GetDisplay();
	game_context_initialize(&cxt);
	#ifdef EMCC
		emscripten_set_main_loop_arg(main_loop, (void *)&(cxt), 0, SDL_TRUE);
	#else
		while (cxt.shouldQuit == SDL_FALSE)
			main_loop(&(cxt));
	#endif
	return (0);
}
