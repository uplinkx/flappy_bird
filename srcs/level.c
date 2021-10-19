/***************************************************************************
 * FILENAME:    level.c
 * DESCRIPTION: File that handles the main game loop.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 18Oct2021
***************************************************************************/

#include "main.h"

// typedef struct	s_scene
// {
// 	SDL_Texture	*texture;
// 	SDL_Rect	*src_rect;

// 	SDL_Texture	*background;

// 	int			*ticks;
// 	int			score;

// 	bool		game_over;

// 	int			pipe_capacity;
// 	int			current_pipe_amount;
// 	t_pipe		*pipes;

// 	int			player_animation;
// 	int			player_loc_y;
// 	int			player_vel_y;
// }				t_scene;

void	*level_select_init(t_game_context *context, SDL_UNUSED void *vp_scene)
{
	t_scene	*scene;
	SDL_Renderer	*renderer;

	scene = new_scene(sizeof(*scene), context, NULL, level_select_close, level_select_update);
	renderer = SDLX_GetDisplay()->renderer;

	scene->texture = IMG_LoadTexture(renderer, "resources/flappy_bird.png");
	scene->background = IMG_LoadTexture(renderer, "resources/flappy_background.png");
	scene->src_rect = carve_flappy_bird_texture();

	scene->ticks = &(context->ticks);
	scene->score = 0;
	scene->game_over = SDL_FALSE;

	scene->pipes.pipe_texture = IMG_LoadTexture(renderer, "resources/flappy_bird.png");
	scene->pipes.src_rect = carve_flappy_bird_texture();
	scene->pipes.pipe_capacity = 10;
	scene->pipes.current_pipe_amount = 0;

	scene->pipes.pipes = SDL_calloc(10, sizeof(*(scene->pipes.pipes)));

	scene->player_animation = FLAPPY_MID;
	scene->player_vel_y = 0;
	scene->player_loc_y = 100;

	return (NULL);
}

void	*level_select_close(t_game_context *context, void *vp_scene)
{
	t_scene	*level;

	level = vp_scene;
	context->init_fn = main_menu_select_init;

	if (level->score > context->hiscore)
	{
		context->hiscore = level->score;
		context->isHiscore = SDL_TRUE;
	}

	return (NULL);
}

void	process_user_input(t_scene *game_state)
{
	const Uint8		*keystate;

	keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_SPACE])
		game_state->player_vel_y = 8;
	// if (keystate[SDL_SCANCODE_R])
	// 	game_context_initialize(game_state);

	Uint32	mres;

	mres = SDL_GetMouseState(NULL, NULL);

	if (SDL_BUTTON(SDL_BUTTON_LEFT) & mres)
		game_state->player_vel_y = 8;
}

void	*level_select_update(SDL_UNUSED t_game_context *context, void *vp_scene)
{
	t_scene	*level;

	level = vp_scene;

	process_user_input(level);
	draw_background(level, SDLX_GetDisplay());

	if (*(level->ticks) % 45 == 0)
		spawn_pipe(&(level->pipes));
	update_active_pipes(&(level->pipes), &(level->score));

	level->player_loc_y -= level->player_vel_y;
	if (level->player_vel_y > -10 && *(level->ticks) % 2 == 0)
		level->player_vel_y += -1;

	level->game_over = pipe_collisions(&(level->pipes), level->player_loc_y);

	draw_pipes(&(level->pipes));
	draw_player(level, SDLX_GetDisplay());
	draw_score(level, SDLX_GetDisplay());

	if (level->game_over == SDL_TRUE)
		game_context_initialize(context);
		// draw_game_over(cxt, display);

	return (NULL);
}
