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
	SDLX_button	exit;
	SDLX_button	redo;
}				t_death_scene;

void	*death_scene_select_init(t_game_context *context, void *vp_scene)
{
	return (NULL);
}

void	*death_scene_select_close(t_game_context *context, void *vp_scene)
{
	return (NULL);
}

void	*death_scene_select_update(t_game_context *context, void *vp_scene)
{
	return (NULL);
}
