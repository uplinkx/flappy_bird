/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 11:30:10 by home              #+#    #+#             */
/*   Updated: 2021/03/07 16:17:07 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	process_user_input(t_game_context *game_state, SDLX_Display *display)
{
	SDL_Event		e;
	const Uint8		*keystate;

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			game_state->active = false;
			break ;
		}
	}
	keystate = SDL_GetKeyboardState(NULL);

		SDL_GameController *controller = NULL;
	int i = 0;
	while (i < SDL_NumJoysticks())
	{
		if (SDL_IsGameController(i))
		{
			controller = SDL_GameControllerOpen(i);
			if (controller)
				break ;
		}
		i++;
	}

	int press = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A);

	if (press)
	{
		SDL_GameControllerRumble(controller, 0x0F00, 0x0100, 70);
		game_state->player_vel_y = 8;
	}

	if (keystate[SDL_SCANCODE_SPACE])
		game_state->player_vel_y = 8;
	if (keystate[SDL_SCANCODE_R])
		game_context_initialize(game_state, display);
}
