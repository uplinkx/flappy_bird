/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carve_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: home <home@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 19:51:55 by home              #+#    #+#             */
/*   Updated: 2021/03/07 16:16:20 by home             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

SDL_Rect	*carve_flappy_bird_texture(void)
{
	int			row;
	int			col;
	SDL_Rect	*result;

	row = 0;
	result = malloc(sizeof(*result) * (3 * 3));
	while (row < 3)
	{
		col = 0;
		while (col < 3)
		{
			result[row * 3 + col].h = 16;
			result[row * 3 + col].w = 16;
			result[row * 3 + col].x = (col * 16);
			result[row * 3 + col].y = (row * 16);
			col++;
		}
		row++;
	}
	return (result);
}
