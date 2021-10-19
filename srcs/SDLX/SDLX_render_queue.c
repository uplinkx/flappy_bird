/***************************************************************************
 * FILENAME:    SDLX_render_queue.c
 * DESCRIPTION: General Functions to render.
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 24Jan2021
***************************************************************************/

#include "SDLX.h"

#define SDLX_QUEUE_DEFAULT_SIZE (5)

SDLX_RenderQueue	default_RenderQueue;

int	SDLX_RenderQueue_Init(SDLX_RenderQueue *dest)
{
	dest->index = 0;
	dest->capacity = SDLX_QUEUE_DEFAULT_SIZE;
	dest->content = SDL_calloc(dest->capacity, sizeof(*dest->content));

	return (EXIT_SUCCESS);
}

void	SDLX_DrawAnimation(SDL_Renderer *renderer, SDLX_Sprite *animation)
{
	size_t		no;
	SDL_Rect	draw_rect;
	SDL_Rect	*ptr_rect;
	SDL_Point	draw_cent;
	SDL_Point	*ptr_cent;

	// SDL_Log("ERROR %zu", animation->sprite_data->cycle);
	no = animation->current % animation->sprite_data->cycle;

	ptr_rect = animation->dst;
	if (ptr_rect == SDLX_NULL_SELF)
		ptr_rect = &(animation->_dst);

	ptr_cent = animation->center;
	if (ptr_cent == SDLX_NULL_SELF)
		ptr_cent = &(animation->_center);

	if (animation->dst != NULL)
	{
		draw_rect = *(ptr_rect);
		draw_rect.h *= DISPLAY_SCALE;
		draw_rect.w *= DISPLAY_SCALE;
		draw_rect.x *= DISPLAY_SCALE;
		draw_rect.y *= DISPLAY_SCALE;
		ptr_rect = &draw_rect;
	}

	if (animation->center != NULL)
	{
		draw_cent = *(ptr_cent);
		draw_cent.x *= DISPLAY_SCALE;
		draw_cent.y *= DISPLAY_SCALE;
		ptr_cent = &draw_cent;
	}

	SDL_RenderCopyEx(renderer,
	animation->sprite_data[no].texture,
	animation->sprite_data[no].src,

	ptr_rect,
	animation->angle,
	ptr_cent,
	animation->flip);

	animation->current += animation->sprite_data[no].skip;
}

void	SDLX_RenderQueue_Flush(SDLX_RenderQueue *queue, SDL_Renderer *renderer, SDL_bool reverse)
{
	size_t	i;

	i = 0;
	if (queue == NULL)
		queue = &(default_RenderQueue);
	if (renderer == NULL)
		renderer = SDLX_GetDisplay()->renderer;

	if (reverse == SDL_TRUE)
	{
		while (i < queue->index)
		{
			SDLX_DrawAnimation(renderer, queue->content[queue->index - 1 - i]);
			i++;
		}
	}
	else
	{
		while (i < queue->index)
		{
			SDLX_DrawAnimation(renderer, queue->content[i]);
			i++;
		}
	}
	queue->index = 0;
}

void	SDLX_DrawAnimation_Direct(SDL_Renderer *renderer, SDLX_Sprite *animation)
{
	size_t		no;

	no = animation->current % animation->sprite_data->cycle;

	SDL_RenderCopyEx(renderer,
	animation->sprite_data[no].texture,
	animation->sprite_data[no].src,
	animation->dst,
	animation->angle,
	animation->center,
	animation->flip);

	animation->current += animation->sprite_data[no].skip;
}

void	SDLX_RenderQueue_Flush_Direct(SDLX_RenderQueue *queue, SDL_Renderer *renderer, SDL_bool reverse)
{
	size_t	i;

	i = 0;
	if (queue == NULL)
		queue = &(default_RenderQueue);
	if (renderer == NULL)
		renderer = SDLX_GetDisplay()->renderer;
	if (reverse == SDL_TRUE)
	{
		while (i < queue->index)
		{
			SDLX_DrawAnimation_Direct(renderer, queue->content[queue->index - 1 - i]);
			i++;
		}
	}
	else
	{
		while (i < queue->index)
		{
			SDLX_DrawAnimation_Direct(renderer, queue->content[i]);
			i++;
		}
	}
	queue->index = 0;
}

void	SDLX_RenderQueue_Add(SDLX_RenderQueue *dst, SDLX_Sprite *src)
{
	if (dst == NULL)
		dst = &(default_RenderQueue);

	if (dst->index + 1 >= dst->capacity)
	{
		dst->capacity = dst->capacity * ALLOC_RATE;
		dst->content = SDL_realloc(dst->content, sizeof(dst->content) * (dst->capacity));
	}

	dst->content[dst->index] = src;
	dst->index += 1;
}

void			SDLX_RenderQueue_Skip(SDLX_RenderQueue *queue, SDL_Renderer *renderer)
{
	size_t	i;
	size_t	no;

	i = 0;
	if (queue == NULL)
		queue = &(default_RenderQueue);
	if (renderer == NULL)
		renderer = SDLX_GetDisplay()->renderer;

	while (i < queue->index)
	{
		no = queue->content[i]->current % queue->content[i]->sprite_data->cycle;
		queue->content[i]->current += queue->content[i]->sprite_data[no].skip;
		i++;
	}
	queue->index = 0;
}
