/***************************************************************************
 * FILENAME:    main_menu.c
 * DESCRIPTION: Main menu scene
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 19Oct2021
***************************************************************************/

#include "main.h"

typedef struct	s_main_menu
{
	SDLX_Sprite	background;

	SDLX_button	play_button;

}				t_main_menu;

void	*main_menu_select_init(t_game_context *context, void *vp_scene)
{
	t_main_menu *scene;

	scene = new_scene(sizeof(*scene), context, "resources/main_menu.png", main_menu_select_close, main_menu_select_update);

	SDLX_Button_Init(&(scene->play_button), fetch_button_sprite, 0, (SDL_Rect){160 / 2 - 32, 100, 64, 32}, NULL);
	SDLX_Style_Button(&(scene->play_button), 0, 1);
	scene->play_button.trigger_fn = button_trigger_scene_switch;
	scene->play_button.meta = context;
	scene->play_button.meta1 = level_select_init;

	(void)vp_scene;
	return (NULL);
}

void	*main_menu_select_close(t_game_context *context, void *vp_scene)
{
	t_main_menu	*scene;

	scene = vp_scene;
	context->ticks = 0;
	// SDL_DestroyTexture(scene->background.sprite_data->texture);
	SDL_free(scene->background.sprite_data);
	SDL_free(scene);

	return (NULL);
}

void	*main_menu_select_update(t_game_context *context, void *vp_scene)
{
	t_main_menu	*scene;

	scene = vp_scene;
	SDLX_Button_Update(&(scene->play_button));
	scene->play_button.sprite.current = context->ticks / 2;

	return (NULL);
}
