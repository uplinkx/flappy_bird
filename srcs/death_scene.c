/***************************************************************************
 * FILENAME:    death_scene.c
 * DESCRIPTION: Manages the death scene
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

typedef struct	s_death_scene
{
	SDL_Rect	s_rect;

	SDLX_button	exit;
	SDLX_button	redo;

	SDLX_Sprite	new;
}				t_death_scene;

void	*death_scene_select_init(t_game_context *context, void *vp_scene)
{
	t_death_scene	*scene;

	scene = new_scene(sizeof(*scene), context, "resources/score.png", death_scene_select_close, death_scene_select_update);

	SDLX_Button_Init(&(scene->redo), fetch_button_sprite, 0, (SDL_Rect){160 / 2 - 30, 125, 60, 30}, NULL);
	SDLX_Style_Button(&(scene->redo), 0, 1);
	scene->redo.trigger_fn = button_trigger_scene_switch;
	scene->redo.meta = context;
	scene->redo.meta1 = level_select_init;

	scene->new = SDLX_Sprite_Static("resources/new_sprite.png");
	scene->new.dst = SDLX_NULL_SELF;
	scene->new._dst = (SDL_Rect){(160 - 95) / 2, 20, 90, 35};

	scene->s_rect.h = 38 * DISPLAY_SCALE;
	scene->s_rect.w = 30 * DISPLAY_SCALE;
	scene->s_rect.y = 170;
	scene->s_rect.x = (180 * 2 + ((int)SDL_log10(context->score)) * scene->s_rect.w) / 2;
	if (context->score <= 0)
		scene->s_rect.x = 180;

	(void)vp_scene;
	return (NULL);
}

void	*death_scene_select_close(t_game_context *context, void *vp_scene)
{
	context->ticks = 0;
	context->score = 0;
	(void)vp_scene;
	return (NULL);
}

void	*death_scene_select_update(t_game_context *context, void *vp_scene)
{
	t_death_scene	*scene;

	scene = vp_scene;
	SDLX_Button_Update(&(scene->redo));
	scene->redo.sprite.current = context->ticks / 2;

	itow(context->score, scene->s_rect, SDLX_GetDisplay());

	if (context->score >= context->hiscore)
		SDLX_RenderQueue_Add(NULL, &(scene->new));

	(void)context;
	return (NULL);
}
