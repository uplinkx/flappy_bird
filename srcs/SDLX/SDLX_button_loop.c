/***************************************************************************
 * FILENAME:    SDLX_button_loop.c
 * DESCRIPTION: Responsible for the way in the button is updated.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 21Jun2021
***************************************************************************/

#include "SDLX.h"

void	SDLX_Button_ReFocus(SDLX_button *button)
{
	button->focus_once_fn(button, button->meta, button->meta_length);
	if (button->focus_no != -1 && button->isLocked == SDL_FALSE)
	{
		button->sprite_fn(&(button->sprite.sprite_data), button->focus_no);
		button->sprite.current = 0;
	}
	button->isFocused = SDL_TRUE;
}

void	SDLX_Button_Focus(SDLX_button *button)
{
	if (button->isFocused == SDL_FALSE) // This activates on-hover, aka once
		SDLX_Button_ReFocus(button);
	else //This continues to activate on hover
		button->focus_fn(button, button->meta, button->meta_length);

	// always active
	button->trigger_fn(button, button->meta, button->meta_length);
}

void	SDLX_Button_Lose_Focus(SDLX_button *button)
{
	if (button->norm_no != -1 && button->isLocked == SDL_FALSE)
	{
		button->sprite_fn(&(button->sprite.sprite_data), button->norm_no);
		button->sprite.current = 0;
	}
	button->isFocused = SDL_FALSE;
	//button lose focus fn
}

/*
// Updates the button based on the data saved in the button class.
// The button has functions for on trigger, on focus, continued focus
// These function should go after all changes, allowing the user to revert
// them if they do not want the automatic changes. This also allows the user to
// create a copy and be able to preform shallow copies.
*/

void	SDLX_Button_Update(SDLX_button *button)
{
	SDL_bool	get_focus;

	if (button->isDisabled == SDL_TRUE)
		return ;

	get_focus = button->get_focus_fn(button, button->meta, button->meta_length);
	if (get_focus == SDL_TRUE) //This could be 'in focus triggers'
		SDLX_Button_Focus(button);
	else if (button->isFocused == SDL_TRUE && get_focus == SDL_FALSE) // Was focused but no longer
		SDLX_Button_Lose_Focus(button);

	button->update_fn(button, button->meta, button->meta_length);

	if (button->isGloballyActive == SDL_TRUE)
		button->trigger_fn(button, button->meta, button->meta_length);

	SDLX_RenderQueue_Add(button->render_dst, &(button->sprite));
	button->sprite.current++;
}

/*
** The button is assumed to non-focusable or focused unnecessarily.
** No focus type of functions are checked. And the button is assumed to be always triggerable
** as long as the button is enabled.
** Main usage is for invisible buttons, or for key trigger type events.
** Or other types of events that you want to always be checked.
*/

void	SDLX_Button_NoFocusUpdate(SDLX_button *button)
{
	if (button->isDisabled == SDL_TRUE)
		return ;

	button->trigger_fn(button, button->meta, button->meta_length);

	SDLX_RenderQueue_Add(button->render_dst, &(button->sprite));
	button->sprite.current++;
}

void	SDLX_Button_TriggerOnly(SDLX_button *button)
{
	if (button->isDisabled == SDL_TRUE)
		return ;

	button->trigger_fn(button, button->meta, button->meta_length);
}