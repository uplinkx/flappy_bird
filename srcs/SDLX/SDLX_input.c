/***************************************************************************
 * FILENAME:    SDLX_input.c
 * DESCRIPTION: Handles the execution of the input mappers
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 04Feb2021
***************************************************************************/

#include "SDLX.h"

void	SDLX_KeyMap(SDLX_input_mapper *key_map, const Uint8 *keystate)
{
	size_t i;

	if (keystate == NULL)
		return ;

	i = 0;
	while (i < key_map->amount)
	{
		*(key_map->map_arr[i].dest) |= keystate[key_map->map_arr[i].param] * key_map->map_arr[i].values;
		i++;
	}
}

void	SDLX_ControllerMap(SDLX_input_mapper *key_map, SDL_GameController *controller)
{
	size_t i;

	if (controller == NULL)
		return ;

	i = 0;
	while (i < key_map->amount)
	{
		*(key_map->map_arr[i].dest) |= SDL_GameControllerGetButton(controller, key_map->map_arr[i].param) * key_map->map_arr[i].values;
		i++;
	}
}

int	SDLX_AxisConvert(SDL_Point *axis)
{
	// SDL_Log("(%d, %d)", axis->x, axis->y);
	if (SDL_abs(axis->x) > SDL_abs(axis->y) && SDL_abs(axis->x) > SDLX_AXIS_THRESHOLD)
	{
		if (axis->x > 0)	return (SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
		else				return (SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	}
	else if (SDL_abs(axis->y) > SDLX_AXIS_THRESHOLD)
	{
		if (axis->y > 0)	return (SDL_CONTROLLER_BUTTON_DPAD_DOWN);
		else				return (SDL_CONTROLLER_BUTTON_DPAD_UP);
	}
	return (0);
}

void	SDLX_toDPAD(SDLX_GameInput *game_input, int set)
{
	if (set == SDL_CONTROLLER_BUTTON_DPAD_DOWN)		game_input->GameInput.button_DPAD_DOWN	= 1;
	if (set == SDL_CONTROLLER_BUTTON_DPAD_UP)		game_input->GameInput.button_DPAD_UP	= 1;
	if (set == SDL_CONTROLLER_BUTTON_DPAD_LEFT)		game_input->GameInput.button_DPAD_LEFT	= 1;
	if (set == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)	game_input->GameInput.button_DPAD_RIGHT	= 1;
}

void	SDLX_GameInput_Mouse_Fill(SDLX_GameInput *dst, SDL_bool convert)
{
	Uint32	mouse_click;

	mouse_click = SDL_GetMouseState(&(dst->GameInput.primary.x), &(dst->GameInput.primary.y));
	SDL_GetRelativeMouseState(&(dst->GameInput.primary_delta.x), &(dst->GameInput.primary_delta.y));

	if (convert == SDL_TRUE)
	{
		SDLX_Mouse_to_Screen(&(dst->GameInput.primary.x), &(dst->GameInput.primary.y));
		// SDLX_Mouse_to_Screen(&(dst->GameInput.primary_delta.x), &(dst->GameInput.primary_delta.y));
	}

	if (SDL_BUTTON(mouse_click) & SDL_BUTTON_LMASK)
		dst->GameInput.button_primleft = SDL_TRUE;
	else if (SDL_BUTTON(mouse_click) & SDL_BUTTON_RMASK)
		dst->GameInput.button_primright = SDL_TRUE;

}

SDL_bool	SDLX_poll(void)
{
	SDL_bool	exit;
	SDL_Event	event;

	exit = SDL_FALSE;
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			exit = SDL_TRUE;
			SDL_Log("Exit");
			return (exit);
		}
	}
	g_GameInput.keystate = SDL_GetKeyboardState(NULL);
	return (exit);
}

void	SDLX_record_input(SDLX_GameInput *from)
{
	if (from == NULL)
		from = &(g_GameInput);

	g_GameInput_prev = *(from);
	SDL_memset(&(from->GameInput), 0, sizeof((from->GameInput)));
}