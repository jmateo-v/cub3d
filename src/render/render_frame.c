/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:12:37 by dogs              #+#    #+#             */
/*   Updated: 2026/01/08 19:32:45 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_ceiling(t_game *g)
{
	uint32_t	*pixels;
	int			x;
	int			y;

	pixels = (uint32_t *)g->frame->pixels;
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixels[y * WIDTH + x] = g->map.ceiling_color;
			x++;
		}
		y++;
	}
}

static void	draw_floor(t_game *g)
{
	uint32_t	*pixels;
	int			x;
	int			y;

	pixels = (uint32_t *)g->frame->pixels;
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixels[y * WIDTH + x] = g->map.floor_color;
			x++;
		}
		y++;
	}
}

void	render_frame(t_game *g)
{
	draw_ceiling(g);
	draw_floor(g);
	cast_rays(g);
}
