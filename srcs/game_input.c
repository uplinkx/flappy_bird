/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 11:30:10 by home              #+#    #+#             */
/*   Updated: 2021/10/18 22:02:13 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	process_user_input(t_game_context *game_state, SDLX_Display *display)
{
	const Uint8		*keystate;

	keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_SPACE])
		game_state->player_vel_y = 8;
	if (keystate[SDL_SCANCODE_R])
		game_context_initialize(game_state, display);

	Uint32	mres;

	mres = SDL_GetMouseState(NULL, NULL);

	if (SDL_BUTTON(SDL_BUTTON_LEFT) & mres)
		game_state->player_vel_y = 8;
}
