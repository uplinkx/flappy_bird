/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLX_button.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 01:10:16 by home              #+#    #+#             */
/*   Updated: 2021/07/25 16:09:58 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDLX.h"

int	SDLX_Button_Init(SDLX_button *dst, int (*sprite_fn)(SDLX_Sprite_Data **, int), int sprite_no, SDL_Rect placement, SDLX_RenderQueue *render_dst)
{
	dst->render_dst = render_dst;

	dst->sprite_fn = sprite_fn;

	SDLX_new_Sprite(&(dst->sprite));
	dst->sprite_fn(&(dst->sprite.sprite_data), sprite_no);
	dst->sprite._dst = placement;

	dst->trigger_box = dst->sprite._dst;

	dst->norm_no = -1;
	dst->focus_no = -1;
	dst->isLocked = SDL_FALSE;

	dst->isDisabled = SDL_FALSE;

	dst->isGloballyActive = SDL_FALSE;
	dst->isFocused = SDL_FALSE;
	dst->isTriggered = SDL_FALSE;

	dst->meta = NULL;
	dst->meta1 = NULL;
	dst->meta_length = 0;

	dst->get_focus_fn = SDLX_Button_onHoverFocus_Mobile;

	dst->focus_fn = SDLX_Button_NULL_fn;
	dst->focus_once_fn = SDLX_Button_NULL_fn;
	dst->trigger_fn = SDLX_Button_NULL_fn;
	dst->update_fn = SDLX_Button_NULL_fn;

	return (EXIT_SUCCESS);
}

void	*SDLX_Button_NULL_fn(SDL_UNUSED SDLX_button *button, SDL_UNUSED void *meta, SDL_UNUSED size_t meta_length)
{
	return NULL;
}

/*
** In a mobile application there is not a clear concept of mouse. It just teleports from spot to spot.
*/
SDL_bool	SDLX_Button_onHoverFocus_Mobile(SDLX_button *self, SDL_UNUSED void *meta, SDL_UNUSED size_t meta_length)
{
	SDL_bool	result;
	SDL_Point	*mouse;

	// The below is the same as:
	// result = SDL_FALSE;
	// if (self->focused == SDL_TRUE)
	// 	result = SDL_TRUE;
	result = self->isFocused;

	// If the mouse has moved then the result will be equal to whether the mouse intersects with the trigger box
	if (g_GameInput.GameInput.primary.x != g_GameInput_prev.GameInput.primary.x || g_GameInput.GameInput.primary.y == g_GameInput_prev.GameInput.primary.y)
	{
		mouse = &(g_GameInput.GameInput.primary);
		result = SDL_PointInRect(mouse, &(self->trigger_box));
	}

	return (result);
}

SDL_bool	SDLX_Button_onHoverFocus(SDLX_button *self, SDL_UNUSED void *meta, SDL_UNUSED size_t meta_length)
{
	SDL_bool	result;
	SDL_Point	*mouse;

	// The below is the same as:
	// result = SDL_FALSE;
	// if (self->focused == SDL_TRUE)
	// 	result = SDL_TRUE;
	result = self->isFocused;

	// If the mouse has moved then the result will be equal to whether the mouse intersects with the trigger box
	if (SDLX_MOUSE_MOVED)
	{
		mouse = &(g_GameInput.GameInput.primary);
		result = SDL_PointInRect(mouse, &(self->trigger_box));
	}

	return (result);
}

void	SDLX_Style_Button(SDLX_button *button, int norm, int hover)
{
	button->focus_no = hover;
	button->norm_no = norm;
}

void	SDLX_Button_Set_fn(SDLX_button *button,
			SDL_bool (*get_focus_fn)(struct SDLX_button *, void *, size_t),
			void *(*focus_fn)(struct SDLX_button *, void *, size_t),
			void *(*focus_once_fn)(struct SDLX_button *, void *, size_t),
			void *(*trigger_fn)(struct SDLX_button *, void *, size_t),
			void *(*update_fn)(struct SDLX_button *, void *, size_t))
{
	if (get_focus_fn != NULL)	{ button->get_focus_fn = get_focus_fn; }
	if (focus_fn != NULL)		{ button->focus_fn = focus_fn; }
	if (focus_once_fn != NULL)	{ button->focus_once_fn = focus_once_fn; }
	if (trigger_fn != NULL)		{ button->trigger_fn = trigger_fn; }
	if (update_fn != NULL)		{ button->update_fn = update_fn; }
}

void	SDLX_Button_Set_UDLR(SDLX_button *button, void *up, void *down, void *left, void *right)
{
	button->up = up;
	button->down = down;
	button->left = left;
	button->right = right;
}
