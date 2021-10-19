/***************************************************************************
 * FILENAME:    SDLX_collide.c
 * DESCRIPTION: Does object to object collisions and returns true
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 06Aug2021
***************************************************************************/

#include "SDLX.h"

SDL_bool	SDLX_Collide_RectToRect(SDLX_collision *hitbox1, SDLX_collision *hitbox2)
{
	SDL_bool	res;

	res = SDL_FALSE;
	SDL_assert(hitbox1->hitbox_ptr != NULL);
	SDL_assert(hitbox2->hitbox_ptr != NULL);
	if (SDL_HasIntersection(hitbox1->hitbox_ptr, hitbox2->hitbox_ptr) == SDL_TRUE)
		res = SDL_TRUE;

	return (res);
}

SDL_bool	SDLX_Collide_RectToARect(SDLX_collision *hitbox1, SDLX_collision *angle_box)
{
	double					angle;
	SDL_bool				res;

	SDL_Point	lt;
	SDL_Point	rt;
	SDL_Point	lb;
	SDL_Point	rb;
	SDL_Rect	*box;
	SDL_Point	norm;

	res = SDL_FALSE;
	angle = angle_box->angle + M_PI;
	box = angle_box->hitbox_ptr;

	norm.x = 0;
	norm.y = 0;
	if (angle_box->center_ptr != NULL)
	{
		norm.x = angle_box->center_ptr->x - (box->w / 2);
		norm.y = angle_box->center_ptr->y - (box->h / 2);
	}

	lt = (SDL_Point){norm.x - (box->w / 2), norm.y + (box->h / 2)};
	rt = (SDL_Point){norm.x + (box->w / 2), norm.y + (box->h / 2)};
	lb = (SDL_Point){norm.x - (box->w / 2), norm.y - (box->h / 2)};
	rb = (SDL_Point){norm.x + (box->w / 2), norm.y - (box->h / 2)};

	lt = SDLX_RotatePoint(&lt, angle);
	rt = SDLX_RotatePoint(&rt, angle);
	lb = SDLX_RotatePoint(&lb, angle);
	rb = SDLX_RotatePoint(&rb, angle);

	lt.x += (box->x + (angle_box->center_ptr->x));
	rt.x += (box->x + (angle_box->center_ptr->x));
	lb.x += (box->x + (angle_box->center_ptr->x));
	rb.x += (box->x + (angle_box->center_ptr->x));

	lt.y += (box->y + (angle_box->center_ptr->y));
	rt.y += (box->y + (angle_box->center_ptr->y));
	lb.y += (box->y + (angle_box->center_ptr->y));
	rb.y += (box->y + (angle_box->center_ptr->y));
	// SDL_RenderDrawLine(SDLX_GetDisplay()->renderer, lt.x, lt.y, rt.x, rt.y);
	// SDL_RenderDrawLine(SDLX_GetDisplay()->renderer, lt.x, lt.y, lb.x, lb.y);
	// SDL_RenderDrawLine(SDLX_GetDisplay()->renderer, rt.x, rt.y, rb.x, rb.y);
	// SDL_RenderDrawLine(SDLX_GetDisplay()->renderer, lb.x, lb.y, rb.x, rb.y);

	if (
		SDL_IntersectRectAndLine(hitbox1->hitbox_ptr, &(lb.x), &(lb.y), &(lt.x), &(lt.y)) ||
		SDL_IntersectRectAndLine(hitbox1->hitbox_ptr, &(lt.x), &(lt.y), &(rt.x), &(rt.y)) ||
		SDL_IntersectRectAndLine(hitbox1->hitbox_ptr, &(lb.x), &(lb.y), &(rb.x), &(rb.y)) ||
		SDL_IntersectRectAndLine(hitbox1->hitbox_ptr, &(rt.x), &(rt.y), &(rb.x), &(rb.y)) ||

		SDL_IntersectRectAndLine(hitbox1->hitbox_ptr, &(rt.x), &(rt.y), &(lb.x), &(lb.y)) || //This one checks if a hitbox is within the larger one.
		SDL_IntersectRectAndLine(hitbox1->hitbox_ptr, &(rb.x), &(rb.y), &(lt.x), &(lt.y)) //This one checks if a hitbox is within the larger one.
		)
		res = SDL_TRUE;

	return (res);
}

SDL_bool	SDLX_Collide_ARectToRect(SDLX_collision *angle_box, SDLX_collision *hitbox1)
{
	return (SDLX_Collide_RectToARect(hitbox1, angle_box));
}

SDL_bool	SDLX_Collide_CircleToRect(SDLX_collision *circle, SDLX_collision *hitbox)
{
	SDL_bool	res;
	int			x, y;
	int			x1, y1;
	int			dx, dy;
	int			r;

	res = SDL_FALSE;
	SDL_assert(circle->hitbox_ptr != NULL);
	SDL_assert(hitbox->hitbox_ptr != NULL);
	x = circle->hitbox_ptr->x + (circle->hitbox_ptr->w / 2);
	y = circle->hitbox_ptr->y + (circle->hitbox_ptr->h / 2);
	x1 = hitbox->hitbox_ptr->x + (hitbox->hitbox_ptr->w / 2);
	y1 = hitbox->hitbox_ptr->y + (hitbox->hitbox_ptr->h / 2);

	r = (circle->hitbox_ptr->w + circle->hitbox_ptr->h) / 4;
	dx = x1 - x;
	dy = y1 - y;

	if (dx * dx + dy * dy < r * r)
		res = SDL_TRUE;

	return (res);
}

SDL_bool	SDLX_Collide_RectToCircle(SDLX_collision *hitbox, SDLX_collision *circle)
{
	return (SDLX_Collide_CircleToRect(circle, hitbox));
}